#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Encoder.cpp"

using namespace std;

class Key {
public:
    virtual std::vector<unsigned char> encodeKey() = 0;
    virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& plaintext) = 0;

    string encryptBoolean(bool plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeBoolean(plaintext)));
    }

    string encryptShort(short plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeShort(plaintext)));
    }

    string encryptInt(int plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeInt(plaintext)));
    }

    string encryptLong(long long plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeLong(plaintext)));
    }

    string encryptFloat(float plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeFloat(plaintext)));
    }

    string encryptDouble(double plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeDouble(plaintext)));
    }

    string encryptChar(char plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeChar(plaintext)));
    }

    string encryptString(const std::string& plaintext) {
        return bytesToHexString(encrypt(Encoder::encodeString(plaintext)));
    }

    virtual std::vector<unsigned char> decrypt(const std::vector<uint8_t>& ciphertext) = 0;

    bool decryptBoolean(const std::string& ciphertext) {
        return Encoder::decodeBoolean(decrypt(hexStringToBytes(ciphertext)));
    }

    short decryptShort(const std::string& ciphertext) {
        return Encoder::decodeShort(decrypt(hexStringToBytes(ciphertext)));
    }

    int decryptInt(const std::string& ciphertext) {
        return Encoder::decodeInt(decrypt(hexStringToBytes(ciphertext)));
    }

    long long decryptLong(const std::string& ciphertext) {
        return Encoder::decodeLong(decrypt(hexStringToBytes(ciphertext)));
    }

    float decryptFloat(const std::string& ciphertext) {
        return Encoder::decodeFloat(decrypt(hexStringToBytes(ciphertext)));
    }

    double decryptDouble(const std::string& ciphertext) {
        return Encoder::decodeDouble(decrypt(hexStringToBytes(ciphertext)));
    }

    char decryptChar(const std::string& ciphertext) {
        return Encoder::decodeChar(decrypt(hexStringToBytes(ciphertext)));
    }

    std::string decryptString(const std::string& ciphertext) {
        return Encoder::decodeString(decrypt(hexStringToBytes(ciphertext)));
    }

    static std::string bytesToHexString(const std::vector<uint8_t>& bytes) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (const auto& byte : bytes) {
            ss << std::setw(2) << static_cast<int>(byte);
        }
        return ss.str();
    }

    static std::vector<uint8_t> hexStringToBytes(const std::string& hexString) {
        std::vector<uint8_t> bytes;
        for (int i = 0; i < hexString.length(); i += 2) {
            std::string byteString = hexString.substr(i, 2);
            uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
            bytes.push_back(byte);
        }
        return bytes;
    }
};