#include <bitset>
#include <cstdint>
#include <vector>
#include <cstring>
#include <cmath>
#include <openssl/sha.h>
#include "ByteBuffer.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "Key.cpp"

namespace mp = boost::multiprecision;

class FastOpeKey: public Key{
private:
    const uint64_t n;
    const double alpha;
    const double beta;
    const double e;
    const uint64_t k;
    uint8_t* kBytes;
    int plaintextBytesPerBlock;
    int ciphertextBytesPerBlock;
    int ciphertextBitsPerByte;
    int64_t ciphertextBitMask;
    int64_t* fmin;
    int64_t* fmax;
    uint8_t bitMasks[9] = {
            0x00,
            0x80,
            0x40,
            0x20,
            0x10,
            0x08,
            0x04,
            0x02,
            0x01
    };

public:
    FastOpeKey(int64_t n, double alpha, double e, int64_t k) : n(n), alpha(alpha), beta(1.0 - alpha), e(e), k(k) {
        kBytes = new uint8_t[sizeof(int64_t)];
        for (size_t i = 0; i < sizeof(int64_t); i++) {
            kBytes[i] = static_cast<uint8_t>((k >> (8 * (sizeof(int64_t) - 1 - i))) & 0xFF);
        }
        fmin = new int64_t[9];
        fmax = new int64_t[9];

        for (int i = 0; i < 9; i++) {
            double factor = pow(e, i) * n;
            fmin[i] = floor(alpha * factor);
            fmax[i] = ceil(beta * factor);
        }
        ciphertextBitsPerByte = 0;
        uint64_t b = n;
        while (b > 0) {
            ciphertextBitsPerByte++;
            b >>= 1;
        }
        ciphertextBitMask = (1 << ciphertextBitsPerByte) - 1;
        int cipherBits = ciphertextBitsPerByte;
        for (int i = 1; i <= 8; i++) {
            if ((cipherBits * i) % 8 == 0) {
                plaintextBytesPerBlock = i;
                break;
            }
        }
        ciphertextBytesPerBlock = plaintextBytesPerBlock * cipherBits / 8;
    }

    std::vector<unsigned char> encodeKey() override {
        ByteBuffer* buffer = new ByteBuffer(2 * sizeof(uint64_t) + 2 * sizeof(double));
        buffer->putLong(n);
        buffer->putDouble(alpha);
        buffer->putDouble(e);
        buffer->putLong(k);
        return buffer->array();
    }

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext) override {
        int blockCount = (plaintext.size() + plaintextBytesPerBlock - 1) / plaintextBytesPerBlock;
        int ciphertextSize = blockCount * ciphertextBytesPerBlock + 1;
        int padding = blockCount * plaintextBytesPerBlock - plaintext.size();
        size_t byteCount = plaintext.size();
        uint8_t* arr = new uint8_t[plaintext.size()];
        memcpy(arr, &plaintext[0], plaintext.size()*sizeof(uint8_t));
        ByteBuffer* plaintextBuffer = new ByteBuffer(arr, static_cast<uint32_t>(byteCount));
        ByteBuffer* ciphertextBuffer = new ByteBuffer(ciphertextSize);
        for (int block = 0; block < blockCount; block++) {
            mp::cpp_int blockCipher = 0;
            for (int i = 0; i < plaintextBytesPerBlock; i++) {
                long long cipher = 0;
                if (plaintextBuffer->position() < plaintext.size()) {
                    uint8_t b = plaintextBuffer->get();
                    cipher = f(0, 0);
                    for (int j = 1; j <= 8; j++) {
                        cipher += ((b & bitMasks[j]) == 0 ? -1 : 1) * f(j, b);
                    }
                }
                blockCipher = blockCipher << (ciphertextBitsPerByte) | cipher;
            }
            std::vector<uint8_t> blockCipherBytes;
            mp::export_bits(blockCipher, std::back_inserter(blockCipherBytes), 8, true);
            if (blockCipherBytes.size() < ciphertextBytesPerBlock) {
                int diff = ciphertextBytesPerBlock - blockCipherBytes.size();
                for (int i = 0; i < diff; i++) {
                    ciphertextBuffer->put((uint8_t)0);
                }
                ciphertextBuffer->putBytes(blockCipherBytes.data(), static_cast<uint32_t>(blockCipherBytes.size()));
            } else {
                ciphertextBuffer -> putBytes(blockCipherBytes.data(), ciphertextBytesPerBlock, blockCipherBytes.size() - ciphertextBytesPerBlock);
            }
        }
        ciphertextBuffer->put((uint8_t)padding);
        return ciphertextBuffer->array();
    }

    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext) override {
        int blockCount = (ciphertext.size() - 1) / ciphertextBytesPerBlock;
        uint8_t plaintextSize = blockCount * plaintextBytesPerBlock - (ciphertext[ciphertext.size() - 1]);
        ByteBuffer plaintextBuffer(plaintextSize);
        size_t byteCount = ciphertext.size();
        uint8_t* newArray = new uint8_t[byteCount];
        memcpy(newArray, &ciphertext[0], ciphertext.size()*sizeof(uint8_t));
        ByteBuffer* ciphertextBuffer = new ByteBuffer(newArray, static_cast<uint32_t>(byteCount));
        for (int block = 0; block < blockCount; block++) {
            std::vector<uint8_t> blockBytes(ciphertextBytesPerBlock);
            ciphertextBuffer->getBytes(blockBytes.data(), static_cast<uint32_t>(blockBytes.size()));
            mp::cpp_int blockCipher;
            mp::import_bits(blockCipher, blockBytes.begin(), blockBytes.end());
            int plaintextOffset = block * plaintextBytesPerBlock;
            for (int i = plaintextBytesPerBlock - 1; i >= 0; i--) {
                auto cipher = (blockCipher & ciphertextBitMask).convert_to<long long>();
                blockCipher >>= ciphertextBitsPerByte;
                uint8_t b = 0;
                long long a = f(0, 0);
                if (cipher >= a) {
                    b |= bitMasks[1];
                }
                for (int j = 1; j < 8; j++) {
                    long long aj = f(j, b);
                    a += ((b & bitMasks[j]) == 0 ? -1 : 1) * aj;
                    if (cipher >= a) {
                        b |= bitMasks[j + 1];
                    }
                }
                if (plaintextOffset + i < plaintextSize) {
                    plaintextBuffer.put(b, plaintextOffset + i);
                }
            }
        }
        return plaintextBuffer.array();
    }

private:
    long long f(int i, uint8_t x) {
        int shift = 8 - i;
        x = (x >> shift) << shift;
        uint8_t hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, kBytes, sizeof(kBytes));
        SHA256_Update(&ctx, &x, sizeof(x));
        SHA256_Final(hash, &ctx);
        mp::cpp_int bi;
        mp::import_bits(bi, hash, hash + sizeof(hash)/sizeof(hash[0]));
        mp::cpp_int result = bi % (fmax[i] - fmin[i]) + fmin[i];
        return result.convert_to<long long>();
    }
};