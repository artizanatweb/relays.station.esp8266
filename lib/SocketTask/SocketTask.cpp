//
// Created by daniel on 20.01.2021.
//

#include "SocketTask.h"

GlobalStore* SocketTask::globalStore = GlobalStore::getInstance();

ConfigStore* SocketTask::configStore = ConfigStore::GetInstance();

void SocketTask::setup() {
    while (!globalStore->serverReady) {
        Serial.println("[SOCKET TASK] Not yet configured!");
        delay(1000);
    }

//    String protocol = "wss://";
    String port = "8443";
//    gatewayAddress = protocol + configStore->gwIp + ":" + port;
    gatewayAddress = configStore->gwIp + ":" + port;

    //
}

void SocketTask::loop() {
    checkRequest();

    if (!globalStore->socketConnected) {
        return;
    }

    client.poll();
}

void SocketTask::checkRequest() {
    if (!(globalStore->connectionRequest > 0)) {
        return;
    }

    if (globalStore->socketConnected) {
        return;
    }

    Serial.println("Open WebSocket connection!");
    connectClient();

    globalStore->connectionRequest = 0;
}

void SocketTask::connectClient() {
    Serial.println("Connect to address");
    Serial.println(gatewayAddress);

    client.onMessage(onMessageCallback);
    client.onEvent(onEventCallback);
    client.setInsecure();
    bool connected = client.connect(gatewayAddress);
    if (connected) {
        Serial.println("[CONNECT] Returns TRUE");
        return;
    }

    Serial.println("[CONNECT] Returns FALSE");
}

void SocketTask::onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void SocketTask::onEventCallback(WebsocketsEvent event, String data) {
    Serial.println("[WebSocket] PLM am primit ceva:");
    Serial.println(data.c_str());
    Serial.println("[WebSocket] Event is: ");
    Serial.println((char) event);

    if (WebsocketsEvent::ConnectionOpened == event) {
        Serial.println("[WebSocket] Connection opened!");
        globalStore->socketConnected = true;
        return;
    }

    if (WebsocketsEvent::ConnectionClosed == event) {
        Serial.println("[WebSocket] Connection closed!");
        globalStore->socketConnected = false;
        return;
    }
}