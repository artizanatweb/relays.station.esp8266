//
// Created by daniel on 12.01.2021.
//

#include "ServerTask.h"

ESP8266WebServer* ServerTask::server = new ESP8266WebServer(80);

GlobalStore* ServerTask::globalStore = GlobalStore::getInstance();

CryptoWrapper* ServerTask::cryptoWrapper = CryptoWrapper::getInstance();

void ServerTask::setup() {
    while (!globalStore->configured) {
        Serial.println("[SERVER TASK] Not yet configured!");
        delay(1000);
    }

    while (!globalStore->wifi) {
        Serial.println("[SERVER TASK] WiFi not connected!");
        delay(1000);
    }

    cryptoWrapper->setup();

    server->on("/connection/request", HTTP_POST, connectionRequestHandler);
    server->begin();

    globalStore->serverReady = true;
}

void ServerTask::loop() {
    if (!globalStore->wifi) {
        return;
    }

    server->handleClient();
}

void ServerTask::connectionRequestHandler() {
    WiFiClient client = server->client();
    if (globalStore->connectionRequest > 0) {
        Serial.println("There is already a request!");
        client.stop();
        return;
    }

    String receivedClientIp = client.remoteIP().toString();
    if (!(cryptoWrapper->config->gwIp == receivedClientIp)) {
        Serial.println("Wrong GW IP address!");
        client.stop();
        return;
    }

    String requestMessage = server->arg("plain");
    if (!(requestMessage.length() > 20)) {
        Serial.println("Wrong body raw payload!");
        client.stop();
        return;
    }

    String message = cryptoWrapper->decrypt(requestMessage);
    if (!(message.length() > 5)) {
        Serial.println("Can't decrypt message!");
        respondError();
        return;
    }

    Serial.println(message);

    const int messageCapacity = 2 * message.length();
    DynamicJsonDocument messageJson(messageCapacity);
    DeserializationError messageError = deserializeJson(messageJson, message);
    if (messageError) {
        Serial.print(F("deserializeJson() failed with code: "));
        Serial.println(messageError.c_str());
        respondError();
        return;
    }

    if (!messageJson.containsKey("srvToken")) {
        Serial.println("Missing srvToken!");
        respondError();
        return;
    }

    String srvToken = messageJson["srvToken"];

    String boardToken = cryptoWrapper->createSession();

    globalStore->session = boardToken + srvToken;
    Serial.print("Session set to: ");
    Serial.println(globalStore->session);

    int dataCapacity = JSON_OBJECT_SIZE(2);
    DynamicJsonDocument data(dataCapacity);
    data["stToken"].set(boardToken.c_str());

    globalStore->connectionRequest++;

    respondSuccess(data.as<JsonObject>());
}

void ServerTask::respondSuccess(JsonObject data) {
    Serial.println("SUCCESS");

    DynamicJsonDocument response(256);
    response["success"] = true;
    response["message"] = "done";
    JsonObject respData = response.createNestedObject("data");
    respData.set(data);

    String jsonString;
    serializeJson(response, jsonString);

    Serial.println(jsonString);

//    server->send(200, "application/json", jsonString.c_str());

    String plainResponse;
    plainResponse = cryptoWrapper->encrypt(jsonString);
    server->send(200, "text/plain", plainResponse.c_str());
}

void ServerTask::respondError() {
    Serial.println("ERROR");

    DynamicJsonDocument response(256);
    response["success"] = false;
    response["message"] = "request failed!";

    String jsonString;
    serializeJson(response, jsonString);

//    server->send(404, "application/json", jsonString.c_str());

    String plainResponse;
    plainResponse = cryptoWrapper->encrypt(jsonString);
    server->send(404, "text/plain", plainResponse.c_str());
}