//
// Created by daniel on 12.01.2021.
//

#ifndef GLOBALSTORE_H
#define GLOBALSTORE_H

#define MAX_RELAYS 4
#define MAX_CONFIG_SIZE 1024

class GlobalStore {
private:
    GlobalStore();
    static GlobalStore* instance_;

public:
    GlobalStore(GlobalStore &other) = delete;
    void operator = (const GlobalStore &) = delete;
    static GlobalStore *getInstance();
    bool configured;
    bool wifi;
};

#endif //GLOBALSTORE_H
