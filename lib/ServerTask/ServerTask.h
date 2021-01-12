//
// Created by daniel on 12.01.2021.
//

#ifndef SERVERTASK_H
#define SERVERTASK_H

#include <Arduino.h>
#include <Scheduler.h>
#include "GlobalStore.h"

class ServerTask : public Task {
public:
    void setup();
    void loop();

private:
    GlobalStore *globalStore;
};

#endif //SERVERTASK_H
