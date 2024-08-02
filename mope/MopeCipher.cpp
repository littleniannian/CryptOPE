//
// Created by Jarvis Yuen on 2024/7/22.
//
#include "../fast/Cipher.h"
#include "MopeKey.cpp"

class MopeCipher : public Cipher{
private:
    Cipher* cipher;

public:
    MopeCipher(Cipher* cipher) {
        this->cipher = cipher;
    }

    Key *generateKey() noexcept(false) override {
        Key* key = cipher->generateKey();
        return new MopeKey(key);
    }

    Key *decodeKey(std::vector<unsigned char> bytes) noexcept(false) override {
        ByteBuffer* buffer = new ByteBuffer(bytes.size());
        buffer->getInt();
        vector<uint8_t> keyBytes(bytes.size() - buffer->position());
        buffer->getBytes(keyBytes.data(), keyBytes.size());
        Key* key = cipher->decodeKey(keyBytes);
        return new MopeKey(key);
    }

};
