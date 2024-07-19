#include <iostream>
#include <string>
#include "ope.hh"

using namespace NTL;

int main() {
    unsigned int noSizes = 7;
    unsigned int plaintextSizes[] = {16, 32, 64,  128, 256, 512, 1024};
    unsigned int ciphertextSizes[] = {32, 64, 128, 256, 288, 768, 1536};
//    const unsigned int AES_KEY_SIZE = 128;
//    const unsigned int bitsPerByte = 8;
//    const unsigned int AES_KEY_BYTES = AES_KEY_SIZE/bitsPerByte;
    std::string key = "secret aes key!!";
    unsigned int ptextsize = 32;
    unsigned int ctextsize = 64;
    OPE * ope = new OPE(key, ptextsize, ctextsize);
    NTL::ZZ enc100 = ope->encrypt(100);
    ZZ dec100 = ope->decrypt(enc100);
    std::cout << "enc_result: " << enc100 << std::endl;
    std::cout << "dec_result: " << dec100 << std::endl;

    delete ope;
}
