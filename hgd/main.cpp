/*
#include <iostream>
#include <string>
#include "ope.hh"

using namespace NTL;

int main() {
    unsigned int noSizes = 7;
    unsigned int plaintextSizes[] = {16, 32, 64,  128, 256, 512, 1024};
    unsigned int ciphertextSizes[] = {32, 64, 128, 256, 288, 768, 1536};
    const unsigned int AES_KEY_SIZE = 128;
    const unsigned int bitsPerByte = 8;
    const unsigned int AES_KEY_BYTES = AES_KEY_SIZE/bitsPerByte;
    std::string key = "secret aes key!!";
    unsigned int ptextsize = 32;
    unsigned int ctextsize = 64;
    OPE * ope = new OPE(std::string(key, AES_KEY_BYTES), ptextsize, ctextsize);
    NTL::ZZ enc = ope->encrypt(ZZFromString("-100"));
    std::string dec = StringFromZZ(ope->decrypt(enc));
    std::cout << "enc_result: " << enc << std::endl;
    std::cout << "dec_result: " << dec << std::endl;
    NTL::ZZ enc2 = ope->encrypt(ZZFromString("-200"));
    std::string dec2 = StringFromZZ(ope->decrypt(enc2));
    std::cout << "enc_result: " << enc2 << std::endl;
    std::cout << "dec_result: " << dec2 << std::endl;
    delete ope;
}
*/
