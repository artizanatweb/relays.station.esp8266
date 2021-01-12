//
// Created by daniel on 10.01.2021.
//

#ifndef CONFIGTASK_H
#define CONFIGTASK_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Scheduler.h>
#include <LittleFS.h>
#include "ConfigStore.h"
#include "Global.h"

class ConfigTask: public Task {
public:
    void setup();
    void loop();

private:
    int fileSize;
    JsonObject jsonObject;
    ConfigStore* configStore;
    bool setConfiguration();
};

#endif //CONFIGTASK_H
