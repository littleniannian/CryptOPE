#include "FastCipher.cpp"
#include <iostream>


int main() {
    FastOpeCipher * fastOpeCipher = new FastOpeCipher();
    FastOpeKey key = fastOpeCipher->generateKey();
    std::vector<unsigned char> res = key.encryptInt(100);
    std::string result = key.bytesToHexString(res);
    std::cout << "encryptRes100: " << result << std::endl;
    int decryptRes = key.decryptInt(res);
    std::cout << "decryptRes: " << decryptRes << std::endl;
    std::vector<unsigned char> res200 = key.encryptInt(200);
    std::string result200 = key.bytesToHexString(res200);
    std::cout << "encryptRes200: " << result200 << std::endl;
    int decryptRes200 = key.decryptInt(res200);
    std::cout << "decryptRes200: " << decryptRes200 << std::endl;
    std::vector<unsigned char> resN200 = key.encryptInt(-200);
    std::string resultN200 = key.bytesToHexString(resN200);
    std::cout << "encryptResultN200: " << resultN200 << std::endl;
    int decryptResN200 = key.decryptInt(resN200);
    std::cout << "encryptResultN200: " << decryptResN200 << std::endl;
    std::vector<unsigned char> encryptStringRes = key.encryptString("aaaa");
    std::string encryptString = key.bytesToHexString(encryptStringRes);
    std::cout << "encryptString: " << encryptString << std::endl;
    std::string decryptString = key.decryptString(encryptStringRes);
    std::cout << "decryptString: " << decryptString << std::endl;
    std::vector<unsigned char> encryptStringResb = key.encryptString("bbbb");
    std::string encryptStringb = key.bytesToHexString(encryptStringResb);
    std::cout << "encryptStringb: " << encryptStringb << std::endl;
    std::string decryptStringb = key.decryptString(encryptStringResb);
    std::cout << "decryptStringb: " << decryptStringb << std::endl;
    delete fastOpeCipher;
}

