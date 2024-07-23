#include <iostream>
#include <cmath>
#include <vector>
#include "FastOpeKey.cpp"
#include "Cipher.cpp"
#include "Key.cpp"

class FastOpeCipher: public Cipher{
private:
    static const int DEFAULT_TAU = 16;
    int tau;

public:
    FastOpeCipher() : tau(DEFAULT_TAU) {}

    int getTau() {
        return tau;
    }

    void setTau(int tau) {
        this->tau = (tau > 0) ? tau : DEFAULT_TAU;
    }

    Key* generateKey() {
        double alphaRandom = 0.8068468161678964;
        double eRandom = 0.9804490731282025;
        long kRandom = 3376402928302743966L;
        double alpha = alphaRandom / 2.0;
        double beta = 1.0 - alpha;
        double e = eRandom * alpha;
        long n = (long)ceil((double)tau / (beta * pow(e, 8)));
        long k = kRandom & 0x7fffffffffffffffL;
        return new FastOpeKey(n, alpha, e, k);
    }

    Key* decodeKey(std::vector<unsigned char> bytes) {
        ByteBuffer* buffer = new ByteBuffer(bytes.size());
        buffer->putBytes(bytes.data(), bytes.size());
        buffer->position(0);
        long n = buffer->getLong();
        double alpha = buffer->getDouble();
        double e = buffer->getDouble();
        long k = buffer->getLong();
        return new FastOpeKey(n, alpha, e, k);
    }
};

