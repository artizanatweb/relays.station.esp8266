//
// Created by daniel on 20.01.2021.
//

#ifndef SOCKETTASK_H
#define SOCKETTASK_H

#include <Arduino.h>
#include <Scheduler.h>
#include <ArduinoWebsockets.h>
#include "GlobalStore.h"
#include "ConfigStore.h"

using namespace websockets;

class SocketTask : public Task {
public:
    void setup();
    void loop();

private:
    static GlobalStore *globalStore;
    static ConfigStore *configStore;
    WebsocketsClient client;
    String gatewayAddress;
    void checkRequest();
    void connectClient();
    static void onMessageCallback(WebsocketsMessage message);
    static void onEventCallback(WebsocketsEvent event, String data);
};

#endif //SOCKETTASK_H
