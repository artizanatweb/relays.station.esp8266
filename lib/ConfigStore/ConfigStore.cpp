//
// Created by daniel on 11.01.2021.
//

#include "ConfigStore.h"

ConfigStore::ConfigStore() {}

bool ConfigStore::configured = false;

ConfigStore* ConfigStore::instance_ = nullptr;

ConfigStore *ConfigStore::GetInstance() {
    if (nullptr == instance_) {
        instance_ = new ConfigStore();
    }

    return instance_;
}

void ConfigStore::configure(JsonObject jsonConfig) {
    if (configured) {
        return;
    }
    Serial.println("Started configuration");

    setPinsObject();

    if (!jsonConfig.containsKey("board")) {
        Serial.println("BOARD settings not found!");
        return;
    }

    if (!jsonConfig.containsKey("wifi")) {
        Serial.println("WIFI settings not found!");
        return;
    }

    if (!jsonConfig.containsKey("relayModules")) {
        Serial.println("RELAYS settings not found!");
        return;
    }

    if (!jsonConfig.containsKey("iot")) {
        Serial.println("IoT settings not found!");
        return;
    }

    JsonObject board = jsonConfig["board"];
    if (!board.containsKey("id")) {
        Serial.println("StationID board setting not found!");
        return;
    }
    stationID = board["id"].as<String>();

    if (!board.containsKey("sleepMode")) {
        Serial.println("sleepMode setting for board not found!");
        return;
    }
    sleepMode = board["sleepMode"].as<bool>();

    if (!board.containsKey("aesKey")) {
        Serial.println("AES KEY setting for board not found!");
        return;
    }
    aesKey = board["aesKey"].as<String>();
    if (64 != aesKey.length()) {
        Serial.println("AES KEY must have 64 characters!");
        return;
    }

    JsonObject wifi = jsonConfig["wifi"];
    if (!wifi.containsKey("ssid")) {
        Serial.println("SSID setting for WiFi not found!");
        return;
    }
    wifiSSID = wifi["ssid"].as<String>();

    if (!wifi.containsKey("passwd")) {
        Serial.println("PASSWD setting for WiFi not found!");
        return;
    }
    wifiPASSWD = wifi["passwd"].as<String>();


    JsonArray relayModules = jsonConfig["relayModules"];
    relaysCount = relayModules.size();

    if (0 >= relaysCount) {
        Serial.println("Board has no setup for relays!");
        return;
    }

    for (int i = 0; i < relaysCount; i++) {
        JsonObject relayPins = relayModules[i].as<JsonObject>();

        RelayModulePins relayModule(
                this->getUsablePin(relayPins["led"]),
                this->getUsablePin(relayPins["button"]),
                this->getUsablePin(relayPins["relay"])
        );
        relayModulePins.push_back(relayModule);
    }

    JsonObject iot = jsonConfig["iot"];
    if (!iot.containsKey("gwIp")) {
        Serial.println("IoT has no setup for Gateway IP address!");
        return;
    }
    gwIp = iot["gwIp"].as<String>();

    if (!iot.containsKey("gwMac")) {
        Serial.println("IoT has no setup for Gateway MAC address!");
        return;
    }
    gwMac = iot["gwMac"].as<String>();

    Serial.println("DONE with config: " + gwMac);

    configured = true;
    GlobalStore *globalStore = GlobalStore::getInstance();
    globalStore->configured = true;
}

void ConfigStore::setPinsObject() {
    pinsObject["D0"] = 16;
    pinsObject["D1"] = 5;
    pinsObject["D2"] = 4;
    pinsObject["D3"] = 0;
    pinsObject["D4"] = 2;
    pinsObject["D5"] = 14;
    pinsObject["D6"] = 12;
    pinsObject["D7"] = 13;
    pinsObject["D8"] = 15;
    pinsObject["D9"] = 3;
    pinsObject["D10"] = 1;
}

uint8_t ConfigStore::getUsablePin(String pinStr) {
    if (!pinsObject.containsKey(pinStr)) {
        return -1;
    }

    return pinsObject[pinStr];
}