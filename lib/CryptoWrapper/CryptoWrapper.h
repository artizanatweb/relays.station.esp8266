//
// Created by daniel on 20.01.2021.
//

#ifndef CRYPTOWRAPPER_H
#define CRYPTOWRAPPER_H

#include <Arduino.h>
#include "PracticalCrypto.h"
#include "ConfigStore.h"

class CryptoWrapper {
private:
    CryptoWrapper();
    static CryptoWrapper* instance_;
    PracticalCrypto crypto;
    char getSecureChar();

public:
    CryptoWrapper(CryptoWrapper &other) = delete;
    void operator = (const CryptoWrapper &) = delete;
    static CryptoWrapper *getInstance();
    ConfigStore* config;
    String encrypt(String plaintext);
    String decrypt(String ciphertext);
    String createSession();
    PracticalCrypto::Status getCryptoStatus();
    void setup();
};

#endif //CRYPTOWRAPPER_H
