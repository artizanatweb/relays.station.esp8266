//
// Created by daniel on 20.01.2021.
//

#ifndef SOCKETTASK_H
#define SOCKETTASK_H

#include <Arduino.h>
#include <Scheduler.h>
#include "GlobalStore.h"

class SocketTask : public Task {
public:
    void setup();
    void loop();

private:
    static GlobalStore *globalStore;
};

#endif //SOCKETTASK_H
