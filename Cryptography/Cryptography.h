#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "CryptographyStorage.cpp"

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>

#include <iostream>

namespace Cryptography {
  class Cryptography;
}

class Cryptography {
  // Function to generate RSA key pair
  inline EVP_PKEY* generate_key_pair();
  // Encryption Function
  inline bool encrypt(const unsigned char* plaintext, int plaintext_len, const unsigned char* key, const unsigned char* iv, unsigned char* ciphertext, int& ciphertext_len);
  // Decryption Function
  inline bool decrypt(const unsigned char* ciphertext, int ciphertext_len, const unsigned char* key, const unsigned char* iv, unsigned char* plaintext, int& plaintext_len);
  // Sign Message Function
  inline bool sign(EVP_PKEY* private_key, const unsigned char* message, int message_len, unsigned char* signature, unsigned int& signature_len);
  // Verify Signature Function
  inline bool verify(EVP_PKEY* public_key, const unsigned char* message, int message_len, const unsigned char* signature, unsigned int signature_len);
};

#endif