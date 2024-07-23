cmake_minimum_required(VERSION 3.28)
project(CryptOPE)

set(CMAKE_CXX_STANDARD 11)
set(NTL_DIR /opt/homebrew/Cellar/ntl/11.5.1)
set(OPENSSL_DIR /opt/homebrew/Cellar/openssl@3/3.3.1)
set(GMP_DIR /opt/homebrew/Cellar/gmp/6.3.0)
set(BOOST_DIR /opt/homebrew/Cellar/boost/1.85.0)

add_executable(CryptOPE cryptdb/main.cpp cryptdb/ope.cc
        cryptdb/hgd.cc
        cryptdb/cwrap.cc
        cryptdb/prng.cc
        cryptdb/zz.cc
        fast/OpeException.cpp
        fast/Encoder.cpp
        fast/Cipher.cpp
        fast/FastCipher.cpp
        fast/Key.cpp
        fast/FastOpeKey.cpp
        fast/FastOPETest.cpp
        fast/ByteBuffer.h
        mope/MopeCipher.cpp
        mope/MopeKey.cpp
        mope/MopeTest.cpp
)

target_include_directories(CryptOPE PUBLIC ${NTL_DIR}/include)
target_link_libraries(CryptOPE ${NTL_DIR}/lib/libntl.a)
target_include_directories(CryptOPE PUBLIC ${OPENSSL_DIR}/include)
target_link_libraries(CryptOPE ${OPENSSL_DIR}/lib/libssl.a)
target_link_libraries(CryptOPE ${OPENSSL_DIR}/lib/libcrypto.a)
target_include_directories(CryptOPE PUBLIC ${GMP_DIR}/include)
target_link_libraries(CryptOPE ${GMP_DIR}/lib/libgmp.a)
target_include_directories(CryptOPE PUBLIC ${BOOST_DIR}/include)

