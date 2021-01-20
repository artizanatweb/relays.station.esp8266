//
// Created by daniel on 20.01.2021.
//

#include "SocketTask.h"

GlobalStore* SocketTask::globalStore = GlobalStore::getInstance();

void SocketTask::setup() {
    while (!globalStore->serverReady) {
        Serial.println("[SOCKET TASK] Not yet configured!");
        delay(1000);
    }
}

void SocketTask::loop() {}