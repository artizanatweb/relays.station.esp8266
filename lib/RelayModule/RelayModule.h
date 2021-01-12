//
// Created by daniel on 25.12.2020.
//

#ifndef RELAYMODULE_H
#define RELAYMODULE_H

#include <Arduino.h>
#include "PushCounters.h"
#include "RelayModulePins.h"

class RelayModule {
public:
    RelayModule();
    RelayModule(int index);
    void setup(RelayModulePins relayModulePins);
    void loop();
    void resetPushTimer();
    void setDefaultLedState(uint8_t newState);
    int index;

private:
    uint8_t ledPin;
    uint8_t buttonPin;
    uint8_t relayPin;
    unsigned long lastPushTimer;
    int pushDelay;
    uint8_t defaultLedState;
    bool run;
    unsigned long lastBlink;
    int blinkDelay;
    void on();
    void off();
    void blink();
    PushCounters *pushCounters;
};

#endif //RELAYMODULE_H
