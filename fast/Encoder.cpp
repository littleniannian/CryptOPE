#include <gmp.h>
#include <cstdint>
#include <string>
#include <vector>
#include "OpeException.cpp"

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
        uint64_t v = static_cast<uint64_t>(value) - std::numeric_limits<int64_t>::min();
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
        std::vector<uint8_t> buffer(4);
        std::memcpy(buffer.data(), &value, 4);

        if ((buffer[0] & 0x80) == 0) { buffer[0] |= 0x80; }
        else {
            for (unsigned char & i : buffer) { i = ~i; }
        }

        return buffer;
    }

    static float decodeFloat(const std::vector<uint8_t>& value) {
        checkLength(&value, 4);

        std::vector<uint8_t> buffer(4);
        std::memcpy(buffer.data(), value.data(), 4);

        if ((buffer[0] & 0x80) != 0) { buffer[0] &= 0x7f; }
        else {
            for (size_t i = 0; i < buffer.size(); i++) { buffer[i] = ~buffer[i]; }
        }

        float result;
        std::memcpy(&result, buffer.data(), 4);
        return result;
    }

    static std::vector<uint8_t> encodeDouble(double value) {
        std::vector<uint8_t> buffer(8);
        std::memcpy(buffer.data(), &value, 8);

        if ((buffer[0] & 0x80) != 0) { buffer[0] &= 0x7f; }
        else {
            for (unsigned char & i : buffer) { i = ~i; }
        }

        return buffer;
    }

    static double decodeDouble(const std::vector<uint8_t>& value) {
        checkLength(&value, 8);

        std::vector<uint8_t> buffer(8);
        std::memcpy(buffer.data(), value.data(), 8);

        if ((buffer[0] & 0x80) == 0) { buffer[0] |= 0x80; }
        else {
            for (size_t i = 0; i < buffer.size(); i++) { buffer[i] = ~buffer[i]; }
        }

        double result;
        std::memcpy(&result, buffer.data(), 8);
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