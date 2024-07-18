#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Encoder.cpp"

class Key {
public:
    virtual std::vector<unsigned char> encodeKey() = 0;
    virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& plaintext) = 0;

    std::vector<unsigned char> encryptBoolean(bool plaintext) {
        return encrypt(Encoder::encodeBoolean(plaintext));
    }

    std::vector<unsigned char> encryptByte(unsigned char plaintext) {
        return encrypt(Encoder::encodeByte(plaintext));
    }

    std::vector<unsigned char> encryptShort(short plaintext) {
        return encrypt(Encoder::encodeShort(plaintext));
    }

    std::vector<unsigned char> encryptInt(int plaintext) {
        return encrypt(Encoder::encodeInt(plaintext));
    }

    std::vector<unsigned char> encryptLong(long long plaintext) {
        return encrypt(Encoder::encodeLong(plaintext));
    }

    std::vector<unsigned char> encryptFloat(float plaintext) {
        return encrypt(Encoder::encodeFloat(plaintext));
    }

    std::vector<unsigned char> encryptDouble(double plaintext) {
        return encrypt(Encoder::encodeDouble(plaintext));
    }

    std::vector<unsigned char> encryptChar(char plaintext) {
        return encrypt(Encoder::encodeChar(plaintext));
    }

    std::vector<unsigned char> encryptString(const std::string& plaintext) {
        return encrypt(Encoder::encodeString(plaintext));
    }

    virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char>& ciphertext) = 0;

    bool decryptBoolean(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeBoolean(decrypt(ciphertext));
    }

    unsigned char decryptByte(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeByte(decrypt(ciphertext));
    }

    short decryptShort(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeShort(decrypt(ciphertext));
    }

    int decryptInt(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeInt(decrypt(ciphertext));
    }

    long long decryptLong(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeLong(decrypt(ciphertext));
    }

    float decryptFloat(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeFloat(decrypt(ciphertext));
    }

    double decryptDouble(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeDouble(decrypt(ciphertext));
    }

    char decryptChar(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeChar(decrypt(ciphertext));
    }

    std::string decryptString(const std::vector<unsigned char>& ciphertext) {
        return Encoder::decodeString(decrypt(ciphertext));
    }

    std::string bytesToHexString(const std::vector<uint8_t>& bytes) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (const auto& byte : bytes) {
            ss << std::setw(2) << static_cast<int>(byte);
        }
        return ss.str();
    }

    std::vector<uint8_t> hexStringToBytes(const std::string& hexString) {
        std::vector<uint8_t> bytes;
        for (int i = 0; i < hexString.length(); i += 2) {
            std::string byteString = hexString.substr(i, 2);
            // 将16进制字符串转换为字节值
            uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
            // 将字节值添加到字节数组中
            bytes.push_back(byte);
        }
        return bytes;
    }
};