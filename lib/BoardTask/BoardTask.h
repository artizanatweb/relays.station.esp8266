//
// Created by daniel on 11.01.2021.
//

#ifndef BOARDTASK_H
#define BOARDTASK_H

#include <Scheduler.h>
#include "Board.h"
#include "GlobalStore.h"

class BoardTask : public Task {
public:
    void setup();
    void loop();

private:
    GlobalStore* globalStore;
    Board* board;
};

#endif //BOARDTASK_H
