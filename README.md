# CryptOPE
This repo have two order-preserving encryption algorithm, fastOPE and hgd ope(from CryptDB)

## Use Case
### FastOPE
FastOPE int,bool,short,char,float,double类型的保序加密，Mope加密后的密文经测试后发现无法保证顺序。
```c++
int main() {
    FastOpeCipher * fastOpeCipher = new FastOpeCipher();
    FastOpeKey key = fastOpeCipher->generateKey();
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
    string res = key.encryptInt(i);
    cout << "encrypt result: " << res << endl;
    int decryptInt = key.decryptInt(res);
    cout << "decrypt result: " << decryptInt << endl;
    }
```
#### 密钥生成
```c++
Key* key = fastOpeCipher->generateKey();
// encodeKey()将密钥转换成字节，可以将字节用Base64编码后进行传输。
key = fastOpeCipher->decodeKey(key->encodeKey());
```
### CryptDB OPE
支持非负整数
```c++
int main() {
    std::string key = "secret aes key!!";
    unsigned int ptextsize = 32;
    unsigned int ctextsize = 64;
    OPE * ope = new OPE(key, ptextsize, ctextsize);
    // 整数
    NTL::ZZ enc100 = ope->encrypt(100);
    ZZ dec100 = ope->decrypt(enc100);
    std::cout << "enc_result: " << enc100 << std::endl;
    std::cout << "dec_result: " << dec100 << std::endl;


    // 浮点数
    std::string doubleString[] = {
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



```
