//
// Created by daniel on 25.12.2020.
//

#ifndef RELAYMODULEPINS_H
#define RELAYMODULEPINS_H

#include <Arduino.h>

class RelayModulePins {
public:
    RelayModulePins();
    RelayModulePins(uint8_t ledPin, uint8_t buttonPin, uint8_t relayPin);
    uint8_t ledPin;
    uint8_t buttonPin;
    uint8_t relayPin;
};

#endif //RELAYMODULEPINS_H
