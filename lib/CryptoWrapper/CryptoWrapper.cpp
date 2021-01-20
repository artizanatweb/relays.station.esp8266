//
// Created by daniel on 20.01.2021.
//

#include "CryptoWrapper.h"

CryptoWrapper::CryptoWrapper() {}

CryptoWrapper* CryptoWrapper::instance_ = nullptr;

CryptoWrapper *CryptoWrapper::getInstance() {
    if (nullptr == instance_) {
        instance_ = new CryptoWrapper();
    }

    return instance_;
}

void CryptoWrapper::setup() {
    config = ConfigStore::GetInstance();
    crypto.setKey(config->aesKey);
    Serial.println("[CRYPTO] The key is:");
    Serial.println(crypto.getKey());
}

String CryptoWrapper::encrypt(String plaintext) {
    return crypto.encrypt(plaintext);
}

String CryptoWrapper::decrypt(String ciphertext) {
    return crypto.decrypt(ciphertext);
}

String CryptoWrapper::createSession() {
//    return crypto.generateKey();
    String key = "";
    for (uint8_t i = 0; i < 64; ++i) {
        key += getSecureChar();
    }
    return key;
}

char CryptoWrapper::getSecureChar() {
    char c = (char)(32 + secureRandom(90));
    int cHex = int(c);

    if (0x5c == cHex) {
        return getSecureChar();
    }
    if (0x22 == cHex) {
        return getSecureChar();
    }
    if (0x20 == cHex) {
        return getSecureChar();
    }

    return c;
}

PracticalCrypto::Status CryptoWrapper::getCryptoStatus() {
    return crypto.lastStatus();
}