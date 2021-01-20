//
// Created by daniel on 11.01.2021.
//

#ifndef CONFIGSTORE_H
#define CONFIGSTORE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "RelayModulePins.h"
#include "Array.h"
#include "GlobalStore.h"

class ConfigStore {
private:
    ConfigStore();
    static ConfigStore* instance_;

public:
    ConfigStore(ConfigStore &other) = delete;
    void operator = (const ConfigStore &) = delete;
    static ConfigStore *GetInstance();
    static bool configured;
    int relaysCount;
    String stationID;
    String aesKey;
    bool sleepMode;
    String wifiSSID;
    String wifiPASSWD;
    String gwIp;
    String gwMac;
    StaticJsonDocument<1024> pinsObject;
    void configure(JsonObject jsonConfig);
    uint8_t getUsablePin(String pinStr);
    void setPinsObject();
    Array<RelayModulePins, MAX_RELAYS> relayModulePins;
};

#endif //CONFIGSTORE_H
