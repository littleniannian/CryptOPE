//
// Created by Jarvis Yuen on 2024/7/22.
//
#include "../fast/Key.cpp"
#include "../fast/ByteBuffer.h"
#include <algorithm>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;
using namespace std;

class MopeKey : public Key{

private:
    Key* key;
    const int offset = 15341;

public:
    explicit MopeKey(Key *key) : key(key) {}

    vector<uint8_t> encodeKey() override {
        vector<uint8_t> keyBytes = key->encodeKey();
        int size = sizeof(uint32_t) + keyBytes.size();
        auto* buffer = new ByteBuffer(size);
        buffer->putInt(offset);
        buffer->putBytes(keyBytes.data(), keyBytes.size());
        return buffer->array();
    }

    vector<unsigned char> encrypt(const vector<unsigned char> &plaintext) override {
        size_t plaintextBytes = plaintext.size();
        vector<uint8_t> temp(plaintextBytes + 1);
        copy(plaintext.begin(), plaintext.end(), temp.begin() + 1);
        mp::cpp_int plain;
        mp::import_bits(plain, temp.begin(), temp.end());
        mp::cpp_int max = getMax(plaintextBytes);
        mp::cpp_int plain2 = plain - offset;
        if (plain2 < 0) {
            plain2 += max;
        }
        plain2 %= max;
        vector<uint8_t> plaintext2;
        mp::export_bits(plain2, std::back_inserter(temp), 8, true);
        if (temp.size() == plaintextBytes) {
            plaintext2 = temp;
        } else if(temp.size() < plaintextBytes) {
            copy(temp.begin(), temp.end(), inserter(plaintext2, plaintext2.begin() + (plaintextBytes - temp.size())));
        } else {
            copy(temp.begin() + (temp.size() - plaintextBytes), temp.end(), back_inserter(plaintext2));
        }
        return key->encrypt(plaintext2);
    }

    vector<unsigned char> decrypt(const vector<uint8_t> &ciphertext) override {
        vector<uint8_t> plaintext2 = key->decrypt(ciphertext);
        size_t plaintextBytes = plaintext2.size();
        vector<uint8_t> temp(plaintextBytes + 1);
        copy(plaintext2.begin(), plaintext2.end(), temp.begin() + 1);
        mp::cpp_int plain2;
        mp::import_bits(plain2, temp.begin(), temp.end());
        mp::cpp_int max = getMax(plaintextBytes);
        mp::cpp_int plain = (plain2 + offset) % max;

        vector<uint8_t> plaintext;
        mp::export_bits(plain, back_inserter(temp), 8, true);
        if (temp.size() == plaintextBytes) {
            plaintext = temp;
        } else if(temp.size() < plaintextBytes) {
            copy(temp.begin(), temp.end(), inserter(plaintext, plaintext.begin() + (plaintextBytes - temp.size())));
        } else {
            copy(temp.begin() + (temp.size() - plaintextBytes), temp.end(), back_inserter(plaintext));
        }
        return plaintext;
    }


    mp::cpp_int getMax(size_t plaintextBytes) {
        mp::cpp_int max = 1;
        for (int i = 0; i < plaintextBytes; i++) {
            max <<= 8;
        }
        return max;
    }

};
