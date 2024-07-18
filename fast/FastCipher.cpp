#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include "FastOpeKey.cpp"

class FastOpeCipher {
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

    FastOpeKey generateKey() {
        double alphaRandom = 0.8068468161678964;
        double eRandom = 0.9804490731282025;
        long kRandom = 3376402928302743966L;
        double alpha = alphaRandom / 2.0;
        double beta = 1.0 - alpha;
        double e = eRandom * alpha;
        long n = (long)ceil((double)tau / (beta * pow(e, 8)));
        long k = kRandom & 0x7fffffffffffffffL;
        return FastOpeKey(n, alpha, e, k);
    }

    FastOpeKey decodeKey(const unsigned char* bytes) {
        std::vector<unsigned char> buffer(bytes, bytes + sizeof(long) + sizeof(double) * 3);
        std::memcpy(&buffer[0], bytes, buffer.size());
        std::vector<unsigned char> bufferCopy(buffer);
        std::vector<unsigned char> nBuf(sizeof(long));
        std::vector<unsigned char> alphaBuf(sizeof(double));
        std::vector<unsigned char> eBuf(sizeof(double));
        std::vector<unsigned char> kBuf(sizeof(long));

        std::copy(bufferCopy.begin(), bufferCopy.begin() + sizeof(long), nBuf.begin());
        std::copy(bufferCopy.begin() + sizeof(long), bufferCopy.begin() + 2 * sizeof(long), alphaBuf.begin());
        std::copy(bufferCopy.begin() + 2 * sizeof(long), bufferCopy.begin() + 3 * sizeof(long), eBuf.begin());
        std::copy(bufferCopy.begin() + 3 * sizeof(long), bufferCopy.end(), kBuf.begin());

        long n = *(long*)nBuf.data();
        double alpha = *(double*)alphaBuf.data();
        double e = *(double*)eBuf.data();
        long k = *(long*)kBuf.data();

        return FastOpeKey(n, alpha, e, k);
    }
};

