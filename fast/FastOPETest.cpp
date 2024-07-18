#include "FastCipher.cpp"
#include <iostream>
using namespace std;

int main() {
    FastOpeCipher * fastOpeCipher = new FastOpeCipher();
    FastOpeKey key = fastOpeCipher->generateKey();
    fastOpeCipher->decodeKey(key.encodeKey());
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
    for(int i : arr) {
        id++;
        vector<unsigned char> res = key.encryptInt(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << id << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
//        int decryptInt = key.decryptInt(res);
//        cout << "decrypt result: " << decryptInt << endl;
    }
    // test bool
    vector<unsigned char> encryptTrueByte = key.encryptBoolean(true);
    string encryptTrueString = key.bytesToHexString(encryptTrueByte);
    bool trueDecrypt = key.decryptBoolean(encryptTrueByte);
    vector<unsigned char> encryptFalseByte = key.encryptBoolean(false);
    string encryptFalseString = key.bytesToHexString(encryptFalseByte);
    bool falseDecrypt = key.decryptBoolean(encryptFalseByte);
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
        vector<unsigned char> res = key.encryptShort(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idShort << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
//        int decryptInt = key.decryptShort(res);
//        cout << "decrypt result: " << decryptInt << endl;
    }

    // test double failed
    cout << "======test double======" << endl;
    double doubleArr[] = {-30000.1,
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
    int idDouble = 0;
    for(double i : doubleArr) {
        idDouble++;
        vector<unsigned char> res = key.encryptDouble(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idDouble << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
//        double decryptDouble = key.decryptDouble(res);
//        cout << "decrypt result: " << decryptDouble << endl;
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
        vector<unsigned char> res = key.encryptChar(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_char_table (id, plaintext, encrypted) VALUES (" << idChar << ",'"<< i <<"'," << "'"<< result << "'" << ");" << endl;
//        char decryptChar = key.decryptChar(res);
//        cout << "decrypt result: " << decryptChar << endl;
    }

    // test long
    cout << "======test long======" << endl;
    short longArr[] = {-30000,
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
    int idLong = 0;
    for(long i : longArr) {
        idLong++;
        vector<unsigned char> res = key.encryptLong(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << idLong << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
//        char decryptChar = key.decryptChar(res);
//        cout << "decrypt result: " << decryptChar << endl;
    }

    // test float failed
    cout << "======test float======" << endl;
    double floatArr[] = {-30000.1,
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
        vector<unsigned char> res = key.encryptFloat(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_table (id, plaintext, encrypted) VALUES (" << floatDouble << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
        double decryptFloat = key.decryptFloat(res);
        cout << "decrypt result: " << decryptFloat << endl;
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
        vector<unsigned char> res = key.encryptString(i);
        string result = key.bytesToHexString(res);
        cout << "INSERT INTO test_char_table (id, plaintext, encrypted) VALUES (" << idString << ","<< i <<"," << "'"<< result << "'" << ");" << endl;
//        string decryptString = key.decryptString(res);
//        cout << "decrypt result: " << decryptString << endl;
    }

    delete fastOpeCipher;
}

