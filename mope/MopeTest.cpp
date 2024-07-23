/*
//
// Created by Jarvis Yuen on 2024/7/23.
//
#include "MopeCipher.cpp"
#include "../fast/FastCipher.cpp"

int main() {
    Cipher* cipher = new FastOpeCipher();
    MopeCipher* mopeCipher = new MopeCipher(cipher);
    Key* key = mopeCipher->generateKey();
    // test short
    cout << "======test int======" << endl;
    short arr[] = {-30000,
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
    int id = 0;
    for(short i : arr) {
        id++;
        string res = key->encryptShort(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << id << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
//        short decryptShort = key->decryptShort(res);
//        cout << "decrypt result: " << decryptShort << endl;
    }
}
*/
