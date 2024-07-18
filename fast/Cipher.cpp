#include "OpeException.cpp"
class Cipher {
public:
    virtual std::vector<unsigned char> generateKey() noexcept(false) = 0;
    virtual std::vector<unsigned char> decodeKey(const std::vector<unsigned char>& bytes) noexcept(false) = 0;
};
