#include <Arduino.h>
#include <Scheduler.h>
#include "ConfigTask.h"
#include "BoardTask.h"
#include "WiFiTask.h"
#include "ServerTask.h"
#include "SocketTask.h"

ConfigTask configTask;
BoardTask boardTask;
WiFiTask wiFiTask;
ServerTask serverTask;
SocketTask socketTask;

void setup() {
    Serial.begin(115200);
    Serial.println("Setup STARTED....");
    delay(5000);

    Scheduler.start(&configTask);
    Scheduler.start(&boardTask);
    Scheduler.start(&wiFiTask);
    Scheduler.start(&serverTask);
    Scheduler.start(&socketTask);

    Scheduler.begin();
}

void loop() {}