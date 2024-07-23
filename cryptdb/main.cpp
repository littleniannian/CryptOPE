/*
#include <iostream>
#include <string>
#include "ope.hh"

using namespace NTL;
using namespace std;

int main() {
    unsigned int noSizes = 7;
    unsigned int plaintextSizes[] = {16, 32, 64,  128, 256, 512, 1024};
    unsigned int ciphertextSizes[] = {32, 64, 128, 256, 288, 768, 1536};
//    const unsigned int AES_KEY_SIZE = 128;
//    const unsigned int bitsPerByte = 8;
//    const unsigned int AES_KEY_BYTES = AES_KEY_SIZE/bitsPerByte;
    // test int
    std::string key = "secret aes key!!";
    unsigned int ptextsize = 96;
    unsigned int ctextsize = 96;
    OPE * ope = new OPE(key, ptextsize, ctextsize);
    // test int 无法对负数进行正确对解密
    cout << "======test int======" << endl;
    int arr[] = {-30000,
                 -20000,
                 -10000,
                 -5000,
                 -2000,
                 -1500,
                 -1000,
                 -500,
                 -100,
                 -10,
                 -5,
                 -1,
                 0,
                 1,
                 5,
                 10,
                 100,
                 500,
                 1000,
                 1500,
                 2000,
                 5000,
                 10000,
                 20000,
                 30000 };
    for (int num : arr) {
        NTL::ZZ encrypt = ope->encrypt(num);
        ZZ decrypt = ope->decrypt(encrypt);
        std::cout << "plain: " << num << " encrypt: " << encrypt << " decrypt: " << decrypt << std::endl;
    }
    cout << "======test string======" << endl;
    // test string 当是负数时保序加密的结果是逆向的
    string arrString[] = {"-30000",
                 "-20000",
                 "-10000",
                 "-5000",
                 "-2000",
                 "-1500",
                 "-1000",
                 "-500",
                 "-100",
                 "-10",
                 "-5",
                 "-1",
                 "0",
                 "1",
                 "5",
                 "10",
                 "100",
                 "500",
                 "1000",
                 "1500",
                 "2000",
                 "5000",
                 "10000",
                 "20000",
                 "30000" };
    for (const string& numString : arrString) {
        NTL::ZZ encrypt = ope->encrypt(ZZFromString(numString));
        string decrypt = StringFromZZ(ope->decrypt(encrypt));
        std::cout << "plain: " << numString << " encrypt: " << encrypt << " decrypt: " << decrypt << std::endl;
    }
    cout << "size of: " << sizeof("5000") * 8 << endl;
    cout << "size of: " << sizeof("10000") * 8 << endl;
    // test double string
    cout << "======test double======" << endl;
    string doubleString[] = {"-30000.1",
                             "-20000.324",
                             "-10000.23",
                             "-5000.436",
                             "-2000.234",
                             "-1500.567",
                             "-1000.234",
                             "-500.123",
                             "-100.12",
                             "-10.56",
                             "-5.23",
                             "-1.1",
                              "0",
                              "1",
                              "5.1",
                              "10.3",
                              "100.1",
                              "500.4",
                              "1000.2",
                              "1500.4",
                              "2000.4",
                              "5000.1",
                              "10000.4",
                              "20000.3",
                              "30000.5" };
    for (const string& doubleStr : doubleString) {
        NTL::ZZ encrypt = ope->encrypt(ZZFromString(doubleStr));
        string decrypt = StringFromZZ(ope->decrypt(encrypt));
        std::cout << "plain: " << doubleStr << " encrypt: " << encrypt << " decrypt: " << decrypt << std::endl;
    }
    delete ope;
}
*/
