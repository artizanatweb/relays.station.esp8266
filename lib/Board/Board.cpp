//
// Created by daniel on 02.01.2021.
//

#include "Board.h"

Board::Board() {}

Board* Board::instance_ = nullptr;

Board *Board::GetInstance() {
    if (nullptr == instance_) {
        instance_ = new Board();
    }

    return instance_;
}

void Board::setup() {
    configStore = ConfigStore::GetInstance();
    relayModulesCount = configStore->relaysCount;

    uint8_t defaultLedStateValue = HIGH;
    if (configStore->sleepMode) {
        defaultLedStateValue = LOW;
    }

    for (int m = 0; m < relayModulesCount; m++) {
        RelayModulePins modulePins = configStore->relayModulePins.at(m);

        RelayModule relayModule(m);
        relayModule.setup(modulePins);

        switch (m) {
            case 0:
                attachInterrupt(digitalPinToInterrupt(modulePins.buttonPin), Board::buttonInterruptHandler1, RISING);
                break;

            case 1:
                attachInterrupt(digitalPinToInterrupt(modulePins.buttonPin), Board::buttonInterruptHandler2, RISING);
                break;

            case 2:
                attachInterrupt(digitalPinToInterrupt(modulePins.buttonPin), Board::buttonInterruptHandler3, RISING);
                break;

            case 3:
                attachInterrupt(digitalPinToInterrupt(modulePins.buttonPin), Board::buttonInterruptHandler4, RISING);
                break;

            default:
                break;
        }

        relayModule.setDefaultLedState(defaultLedStateValue);
        relayModule.resetPushTimer();
        relayModules.push_back(relayModule);
    }
}

void Board::loop() {
    for (int i = 0; i < (int)relayModules.size(); i++) {
        relayModules.at(i).loop();
    }
}

ICACHE_RAM_ATTR void Board::buttonInterruptHandler1() {
    PushCounters *counters  = PushCounters::getInstance();
    counters->counters[0]++;
}

ICACHE_RAM_ATTR void Board::buttonInterruptHandler2() {
    PushCounters *counters  = PushCounters::getInstance();
    counters->counters[1]++;
}

ICACHE_RAM_ATTR void Board::buttonInterruptHandler3() {
    PushCounters* counters  = PushCounters::getInstance();
    counters->counters[2]++;
}

ICACHE_RAM_ATTR void Board::buttonInterruptHandler4() {
    PushCounters *counters  = PushCounters::getInstance();
    counters->counters[3]++;
}