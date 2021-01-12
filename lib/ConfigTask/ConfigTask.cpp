//
// Created by daniel on 10.01.2021.
//

#include "ConfigTask.h"

void ConfigTask::setup() {
    fileSize = (int) MAX_CONFIG_SIZE;

    configStore = ConfigStore::GetInstance();

    if (!setConfiguration()) {
        while (true) {
            Serial.println("Can't finish config!");
            delay(100000);
        }
    }

    LittleFS.end();
}

void ConfigTask::loop() {}

bool ConfigTask::setConfiguration() {
    bool mountedFileSystem = LittleFS.begin();
    if (!mountedFileSystem) {
        return false;
    }

    if (!LittleFS.exists("/config.json")) {
        LittleFS.end();
        return false;
    }

    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile) {
        LittleFS.end();
        return false;
    }

    int configSize = configFile.size();
    if (fileSize < configSize) {
        LittleFS.end();
        return false;
    }

    DynamicJsonDocument jsonDocument(fileSize);
    DeserializationError error = deserializeJson(jsonDocument, configFile);
    if (error) {
        LittleFS.end();
        return false;
    }

    jsonObject = jsonDocument.as<JsonObject>();

    configStore->configure(jsonObject);

    return true;
}