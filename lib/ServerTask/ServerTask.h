//
// Created by daniel on 12.01.2021.
//

#ifndef SERVERTASK_H
#define SERVERTASK_H

#include <Arduino.h>
#include <Scheduler.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "GlobalStore.h"
#include "CryptoWrapper.h"
#include "PracticalCrypto.h"
#include "ConfigStore.h"

class ServerTask : public Task {
public:
    void setup();
    void loop();

private:
    static ESP8266WebServer* server;
    static GlobalStore* globalStore;
    static CryptoWrapper* cryptoWrapper;
    static void connectionRequestHandler();
    static void respondSuccess(JsonObject data);
    static void respondError();
};

#endif //SERVERTASK_H
