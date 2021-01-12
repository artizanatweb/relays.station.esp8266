//
// Created by daniel on 11.01.2021.
//

#ifndef BOARDTASK_H
#define BOARDTASK_H

#include <Scheduler.h>
#include "ConfigStore.h"
#include "Board.h"

class BoardTask : public Task {
public:
    void setup();
    void loop();

private:
    ConfigStore* configStore;
    Board* board;
};

#endif //BOARDTASK_H
