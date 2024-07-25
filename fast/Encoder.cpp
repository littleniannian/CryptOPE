#include <gmp.h>
#include <cstdint>
#include <string>
#include <vector>
#pragma once

class Encoder {
public:
    Encoder() = delete;

    static std::vector<uint8_t> encodeBoolean(bool value) {
        return {static_cast<uint8_t>(value)};
    }

    static bool decodeBoolean(const std::vector<uint8_t>& value) {
        checkLength(&value, 1);
        return value[0] != 0;
    }

    static std::vector<uint8_t> encodeShort(int16_t value) {
        uint16_t v = static_cast<uint16_t>(value) - std::numeric_limits<int16_t>::min();
        return {
                static_cast<uint8_t>(v >> 8),
                static_cast<uint8_t>(v)
        };
    }

    static int16_t decodeShort(const std::vector<uint8_t>& value) {
        checkLength(&value, 2);
        uint16_t v = static_cast<uint16_t>(value[0]) << 8 | value[1];
        return static_cast<int16_t>(v) + std::numeric_limits<int16_t>::min();
    }

    static std::vector<uint8_t> encodeInt(int32_t value) {
        uint32_t v = static_cast<uint32_t>(value) - std::numeric_limits<int32_t>::min();
        return {
                static_cast<uint8_t>(v >> 24),
                static_cast<uint8_t>(v >> 16),
                static_cast<uint8_t>(v >> 8),
                static_cast<uint8_t>(v)
        };
    }

    static int32_t decodeInt(const std::vector<uint8_t>& value) {
        checkLength(&value, 4);
        uint32_t v = static_cast<uint32_t>(value[0]) << 24 |
                     static_cast<uint32_t>(value[1]) << 16 |
                     static_cast<uint32_t>(value[2]) << 8 |
                     static_cast<uint32_t>(value[3]);
        return static_cast<int32_t>(v) + std::numeric_limits<int32_t>::min();
    }

    static std::vector<uint8_t> encodeLong(int64_t value) {
        uint64_t v = static_cast<int64_t>(value) - std::numeric_limits<int64_t>::min();
        return {
                static_cast<uint8_t>(v >> 56),
                static_cast<uint8_t>(v >> 48),
                static_cast<uint8_t>(v >> 40),
                static_cast<uint8_t>(v >> 32),
                static_cast<uint8_t>(v >> 24),
                static_cast<uint8_t>(v >> 16),
                static_cast<uint8_t>(v >> 8),
                static_cast<uint8_t>(v)
        };
    }

    static int64_t decodeLong(const std::vector<uint8_t>& value) {
        checkLength(&value, 8);
        uint64_t v = static_cast<uint64_t>(value[0]) << 56 |
                     static_cast<uint64_t>(value[1]) << 48 |
                     static_cast<uint64_t>(value[2]) << 40 |
                     static_cast<uint64_t>(value[3]) << 32 |
                     static_cast<uint64_t>(value[4]) << 24 |
                     static_cast<uint64_t>(value[5]) << 16 |
                     static_cast<uint64_t>(value[6]) << 8 |
                     static_cast<uint64_t>(value[7]);
        return static_cast<int64_t>(v) + std::numeric_limits<int64_t>::min();
    }

    static std::vector<uint8_t> encodeFloat(float value) {
        int32_t floatInt;
        memcpy(&floatInt, &value, sizeof(value));
        if (floatInt <0) {
            floatInt = -floatInt - std::numeric_limits<int32_t>::max();
        }
        return encodeInt(floatInt);
    }

    static float decodeFloat(const std::vector<uint8_t>& value) {
        checkLength(&value, 4);

        int32_t floatInt = decodeInt(value);
        if (floatInt < 0) {
            floatInt = -floatInt + std::numeric_limits<int32_t>::max();
        }
        float result;
        memcpy(&result, &floatInt, sizeof(result));
        return result;
    }

    static std::vector<uint8_t> encodeDouble(double value) {
        int64_t doubleInt;
        memcpy(&doubleInt, &value, sizeof(value));
        // 需要一个算法保证doubleInt和value一样是单调递增的，且不改变doubleInt的符号
        if (doubleInt <0) {
            doubleInt = -doubleInt - std::numeric_limits<int64_t>::max();
        }
        return encodeLong(doubleInt);
    }

    static double decodeDouble(const std::vector<uint8_t>& value) {
        checkLength(&value, 8);
        int64_t doubleInt = decodeLong(value);
        if (doubleInt < 0) {
            doubleInt = -doubleInt + std::numeric_limits<int64_t>::max();
        }
        double result;
        memcpy(&result, &doubleInt, sizeof(result));
        return result;
    }

    static std::vector<uint8_t> encodeChar(char value) {
        return {
                static_cast<uint8_t>(value >> 8),
                static_cast<uint8_t>(value & 0xff)
        };
    }

    static char decodeChar(const std::vector<uint8_t>& value) {
        checkLength(&value, 2);
        return static_cast<char>((value[0] << 8) | value[1]);
    }

    static std::vector<uint8_t> encodeString(const std::string& value) {
        if (value.empty()) {
            return {};
        }
        return {value.begin(), value.end()};
    }

    static std::string decodeString(const std::vector<uint8_t>& value) {
        return {value.begin(), value.end()};
    }

private:
    static void checkNull(const std::vector<uint8_t>* value) {
        if (value == nullptr) {
            throw std::runtime_error("Input value is null.");
        }
    }

    static void checkLength(const std::vector<uint8_t>* value, size_t expectedLength) {
        checkNull(value);
        if (value->size() != expectedLength) {
            throw std::runtime_error("Invalid byte array length.");
        }
    }
};