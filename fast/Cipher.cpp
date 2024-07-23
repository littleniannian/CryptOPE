#include "Key.cpp"
#pragma once

class Cipher {
public:
    virtual Key* generateKey() noexcept(false) = 0;
    virtual Key* decodeKey(std::vector<unsigned char> bytes) noexcept(false) = 0;
};
