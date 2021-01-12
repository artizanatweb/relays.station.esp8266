#include <Arduino.h>
#include <Scheduler.h>
#include "ConfigTask.h"
#include "BoardTask.h"

ConfigTask configTask;
BoardTask boardTask;

void setup() {
    Serial.begin(115200);
    Serial.println("Setup STARTED....");
    delay(2000);

    Scheduler.start(&configTask);
    Scheduler.start(&boardTask);

    Scheduler.begin();
}

void loop() {}