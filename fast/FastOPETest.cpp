#include "FastCipher.cpp"
#include <iostream>
#include "Key.cpp"
#include <chrono>
using namespace std;

int main() {
    FastOpeCipher * fastOpeCipher = new FastOpeCipher();
    Key* key = fastOpeCipher->generateKey();
    key = fastOpeCipher->decodeKey(key->encodeKey());
    // test int
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
    int id = 0;
    for (int i: arr) {
       id++;
        string res = key->encryptInt(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << id << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
        int decryptInt = key->decryptInt(res);
        cout << "decrypt result: " << decryptInt << endl;
    }

    // test bool
    cout << "======test bool======" << endl;
    string encryptTrueString = key->encryptBoolean(true);
    bool trueDecrypt = key->decryptBoolean(encryptTrueString);
    string encryptFalseString = key->encryptBoolean(false);
    bool falseDecrypt = key->decryptBoolean(encryptFalseString);
    cout << "encryptTrueString: " << encryptTrueString << " encryptFalseString: " << encryptFalseString
    << " trueDecrypt: " << trueDecrypt
    << " falseDecrypt: " << falseDecrypt
    << endl;

    // test short
    cout << "======test short======" << endl;
    short shortArr[] = {-30000,
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
    int idShort = 0;
    for(short i : shortArr) {
        idShort++;
        string res = key->encryptShort(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idShort << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
        // int decryptInt = key->decryptShort(res);
        // cout << "decrypt result: " << decryptInt << endl;
    }

    // test double failed
    cout << "======test double======" << endl;
    double doubleArr[] = {-30000.1,
                        -20000.3,
                        -1
                        -10000.2,
                        -10000.1,
                        -2000.3,
                        -1500.1,
                        -1000.2,
                        -500.8,
                        -100.9,
                        -10.1,
                        -5.2,
                        -1.3,
                        0,
                        1.3,
                        5.2,
                        10.4,
                        100.8,
                        500.5,
                        1000.4,
                        1500.2,
                        2000.4,
                        5000.3,
                        10000.2,
                        20000.1,
                        30000.5 };
    int idDouble = 0;
    for(double i : doubleArr) {
        idDouble++;
        string res = key->encryptDouble(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idDouble << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
        // double decryptDouble = key->decryptFloat(res);
        // cout << "decrypt result: " << decryptDouble << endl;
    }

    // test char
    cout << "======test char======" << endl;
    char charArr[] = {'a',
                          'b',
                          'c',
                          'd',
                          'e',
                          'f',
                          'g',
                          'h',
                          'i',
                          'j',
                          'k',
                          'i',
                          'm',
                          'n',
                          'o',
                          'p',
                          'q',
                          'r',
                          's',
                          't',
                          'u',
                          'v',
                          'w',
                          'x',
                          'y',
                          'z'};
    int idChar = 0;
    for(char i : charArr) {
        idChar++;
        string res = key->encryptChar(i);
        cout << "INSERT INTO test_char_table (id, plaintext, encrypted) VALUES (" << idChar << ",'"<< i <<"'," << "'"<< res << "'" << ");" << endl;
//        char decryptChar = key.decryptChar(res);
//        cout << "decrypt result: " << decryptChar << endl;
    }

    // test long
    cout << "======test long======" << endl;
    long longArr[] = {-30000,
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
                        30000,
                        9223372036854775807};
    int idLong = 0;
    for(long i : longArr) {
        idLong++;
        string res = key->encryptLong(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idLong << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
        // long decryptLong = key->decryptLong(res);
        // cout << "decrypt result: " << decryptLong << endl;
    }

    // test float
    cout << "======test float======" << endl;
    float floatArr[] = {-30000.1,
                          -20000.3,
                          -10000.2,
                          -5000.5,
                          -2000.3,
                          -1500.1,
                          -1000.2,
                          -500.8,
                          -100.9,
                          -10.1,
                          -5.2,
                          -1.3,
                          0,
                          1.8,
                          5.2,
                          10.4,
                          100.8,
                          500.5,
                          1000.4,
                          1500.2,
                          2000.4,
                          5000.3,
                          10000.2,
                          20000.1,
                          30000.5 };
    int floatDouble = 0;
    for(float i : floatArr) {
        floatDouble++;
        string res = key->encryptFloat(i);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << floatDouble << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
//        double decryptFloat = key.decryptFloat(res);
//        cout << "decrypt result: " << decryptFloat << endl;
    }

    // test string failed
    cout << "======test string======" << endl;
    string stringArr[] = {
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
    int idString = 0;
    for(const string& i : stringArr) {
        idString++;
        string res = key->encryptString(i);
        cout << "INSERT INTO test_char_table (id, plaintext, encrypted) VALUES (" << idString << ","<< i <<"," << "'"<< res << "'" << ");" << endl;
//        string decryptString = key.decryptString(res);
//        cout << "decrypt result: " << decryptString << endl;
    }

    delete fastOpeCipher;
}

