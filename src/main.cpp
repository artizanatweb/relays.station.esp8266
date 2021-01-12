#include <Arduino.h>
#include <Scheduler.h>
#include "ConfigTask.h"
#include "BoardTask.h"
#include "WiFiTask.h"

ConfigTask configTask;
BoardTask boardTask;
WiFiTask wiFiTask;

void setup() {
    Serial.begin(115200);
    Serial.println("Setup STARTED....");
    delay(2000);

    Scheduler.start(&configTask);
    Scheduler.start(&boardTask);
    Scheduler.start(&wiFiTask);

    Scheduler.begin();
}

void loop() {}