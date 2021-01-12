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

    setPinsObject();

    if (!jsonConfig.containsKey("board")) {
        Serial.println("BOARD settings not found!");
        return;
    }

    if (!jsonConfig.containsKey("wifi")) {
        Serial.println("WIFI settings not found!");
    }

    if (!jsonConfig.containsKey("relayModules")) {
        Serial.println("RELAYS settings not found!");
    }

    JsonObject board = jsonConfig["board"];
    if (board.containsKey("id")) {
        stationID = board["id"].as<String>();
    }

    if (board.containsKey("sleepMode")) {
        sleepMode = board["sleepMode"].as<bool>();
    }


    JsonObject wifi = jsonConfig["wifi"];
    if (wifi.containsKey("ssid")) {
        wifiSSID = wifi["ssid"].as<String>();
    }

    if (wifi.containsKey("passwd")) {
        wifiPASSWD = wifi["passwd"].as<String>();
    }


    JsonArray relayModules = jsonConfig["relayModules"];
    relaysCount = relayModules.size();
    for (int i = 0; i < relaysCount; i++) {
        JsonObject relayPins = relayModules[i].as<JsonObject>();

        RelayModulePins relayModule(
                this->getUsablePin(relayPins["led"]),
                this->getUsablePin(relayPins["button"]),
                this->getUsablePin(relayPins["relay"])
        );
        relayModulePins.push_back(relayModule);
    }


    configured = true;
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