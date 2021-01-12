//
// Created by daniel on 11.01.2021.
//

#include "BoardTask.h"
#include "PushCounters.h"

void BoardTask::setup() {
    configStore = ConfigStore::GetInstance();
    while (!configStore->configured) {
        Serial.println("Not yet configured!");
        delay(1000);
    }

    PushCounters *pushCounters  = PushCounters::getInstance();
    pushCounters->resetCounters();

    board = Board::GetInstance();
    board->setup();
}

void BoardTask::loop() {
    board->loop();
}