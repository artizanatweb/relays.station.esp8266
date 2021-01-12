//
// Created by daniel on 12.01.2021.
//

#include "WiFiTask.h"

void WiFiTask::setup() {
    globalStore = GlobalStore::getInstance();
    while (!globalStore->configured) {
        Serial.println("[WIFI TASK] Not yet configured!");
        delay(1000);
    }

    configStore = ConfigStore::GetInstance();

    WiFi.begin(configStore->wifiSSID, configStore->wifiPASSWD);

    while (WL_CONNECTED != WiFi.status()) {
        delay(500);
    }

    Serial.println("WiFi connected!");
    Serial.print("WiFi IP is:");
    Serial.println(WiFi.localIP());

    WiFi.setAutoReconnect(true);
    globalStore->wifi = true;
}

void WiFiTask::loop() {
    delay(500);

    if (WL_CONNECTED == WiFi.status()) {
        if (!globalStore->wifi) {
            globalStore->wifi = true;
            Serial.println("WiFi connected!");
        }
        return;
    }

    Serial.println("WiFi disconnected!");
    globalStore->wifi = false;

    // auto reconnect is on
}