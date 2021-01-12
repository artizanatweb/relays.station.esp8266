//
// Created by daniel on 12.01.2021.
//

#include "GlobalStore.h"

GlobalStore::GlobalStore() : configured(false), wifi(false) {}

GlobalStore* GlobalStore::instance_ = nullptr;

GlobalStore *GlobalStore::getInstance() {
    if (nullptr == instance_) {
        instance_ = new GlobalStore();
    }

    return instance_;
}