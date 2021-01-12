//
// Created by daniel on 25.12.2020.
//

#include <Arduino.h>
#include "RelayModulePins.h"

RelayModulePins::RelayModulePins() {}

RelayModulePins::RelayModulePins(uint8_t ledPin, uint8_t buttonPin, uint8_t relayPin) : ledPin(ledPin), buttonPin(buttonPin), relayPin(relayPin) {}