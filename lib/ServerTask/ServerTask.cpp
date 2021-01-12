//
// Created by daniel on 12.01.2021.
//

#include "ServerTask.h"

void ServerTask::setup() {
    globalStore = GlobalStore::getInstance();
    while (!globalStore->configured) {
        Serial.println("[SERVER TASK] Not yet configured!");
        delay(1000);
    }

    while (!globalStore->wifi) {
        Serial.println("[SERVER TASK] WiFi not connected!");
        delay(1000);
    }


}