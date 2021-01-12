//
// Created by daniel on 25.12.2020.
//

#include "PushCounters.h"

PushCounters::PushCounters() {}

PushCounters* PushCounters::instance_ = nullptr;

PushCounters *PushCounters::getInstance() {
    if (nullptr == instance_) {
        instance_ = new PushCounters();
    }

    return instance_;
}

void PushCounters::resetCounters() {
    counters.clear();

    for (int i = 0; i < MAX_RELAYS; i++) {
        counters.push_back(0);
    }
}
