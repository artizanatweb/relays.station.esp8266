//
// Created by daniel on 12.01.2021.
//

#ifndef WIFITASK_H
#define WIFITASK_H

#include <Arduino.h>
#include <Scheduler.h>
#include <ESP8266WiFi.h>
#include "GlobalStore.h"
#include "ConfigStore.h"

class WiFiTask : public Task {
public:
    void setup();
    void loop();

private:
    GlobalStore* globalStore;
    ConfigStore* configStore;
};

#endif //WIFITASK_H
