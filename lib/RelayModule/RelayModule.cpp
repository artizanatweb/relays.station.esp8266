//
// Created by daniel on 25.12.2020.
//

#include "RelayModule.h"

RelayModule::RelayModule() {}

RelayModule::RelayModule(int index) : index(index) {
    pushCounters = PushCounters::getInstance();
    run = false;

    pushDelay = 700;
    defaultLedState = LOW;
    blinkDelay = 700;
}

void RelayModule::setup(RelayModulePins relayModulePins) {
    ledPin = relayModulePins.ledPin;
    buttonPin = relayModulePins.buttonPin;
    relayPin = relayModulePins.relayPin;

    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(relayPin, OUTPUT);

    lastPushTimer = millis();
}

void RelayModule::loop() {
    blink();

    unsigned long actualTimer = millis();

    int pushCounterValue = pushCounters->counters[index];

    if ((int)(actualTimer - lastPushTimer) < pushDelay) {
        if (pushCounterValue > 0) {
            pushCounters->counters[index] = 0;
        }
        return;
    }

    if (pushCounterValue <= 0) {
        return;
    }

    pushCounters->counters[index] = 0;

    Serial.println("Button pushed");

    if (run) {
        off();
        resetPushTimer();
        return;
    }

    on();
    resetPushTimer();
}

void RelayModule::resetPushTimer() {
    lastPushTimer = millis();
}

void RelayModule::setDefaultLedState(uint8_t newState) {
    if (defaultLedState == newState) {
        return;
    }

    if (HIGH == newState) {
        defaultLedState = HIGH;
    }

    if (LOW == newState) {
        defaultLedState = LOW;
    }

    if (!run) {
        digitalWrite(ledPin, defaultLedState);
    }
}

void RelayModule::on() {
    run = true;
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, digitalRead(ledPin)^1);
    lastBlink = millis();
}

void RelayModule::off() {
    run = false;
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, defaultLedState);
}

void RelayModule::blink() {
    if (!run) {
        return;
    }

    unsigned long nowTime = millis();
    if ((int)(nowTime - lastBlink) < blinkDelay) {
        return;
    }

    lastBlink = nowTime;

    digitalWrite(ledPin, digitalRead(ledPin)^1);
}