# CryptOPE
This repo have two order-preserving encryption algorithm, fastOPE and hgd ope(from CryptDB)

## Use Case
### FastOPE
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
### CryptDB OPE
```c++
int main() {
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

```
