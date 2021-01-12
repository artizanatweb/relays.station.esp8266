//
// Created by daniel on 02.01.2021.
//

#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include "RelayModulePins.h"
#include "RelayModule.h"
#include "ConfigStore.h"
#include "PushCounters.h"
#include "Array.h"
#include "GlobalStore.h"

class Board {
private:
    Board();
    static Board* instance_;

public:
    Board(Board &other) = delete;
    void operator = (const Board &) = delete;
    static Board *GetInstance();
    void setup();
    void loop();
    ConfigStore* configStore;
    int relayModulesCount;
    Array<RelayModule, MAX_RELAYS> relayModules;
    static void buttonInterruptHandler1();
    static void buttonInterruptHandler2();
    static void buttonInterruptHandler3();
    static void buttonInterruptHandler4();
};

#endif //BOARD_H
