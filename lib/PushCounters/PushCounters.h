//
// Created by daniel on 25.12.2020.
//

#ifndef PUSHCOUNTERS_H
#define PUSHCOUNTERS_H

#include <Arduino.h>
#include "Array.h"
#include "GlobalStore.h"

class PushCounters {
private:
    PushCounters();
    static PushCounters* instance_;

public:
    PushCounters(PushCounters &others) = delete;
    void operator = (const PushCounters &) = delete;
    static PushCounters *getInstance();
    Array<int, MAX_RELAYS> counters;
    void resetCounters();
};

#endif //PUSHCOUNTERS_H
