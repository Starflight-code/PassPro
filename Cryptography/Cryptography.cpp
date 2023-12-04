#ifndef CRYPTOGRAPHY_CPP
#define CRYPTOGRAPHY_CPP

// #include "CryptographyStorage.h"
#include <memory>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdexcept>

class Cryptography {
  public:
  Cryptography(const unsigned char* key) : key_(key) {
    OpenSSL_add_all_algorithms();
  }

  ~Cryptography() {
    EVP_cleanup();
  }

  private:
  const unsigned char* key_;
  /**
   * @brief Encrypts the File using openssl
   * @param plaintext character pointer that is to be encrypted
   * @param plaintextLength int length of the message
   * @param ciphertext character pointer of the encrypted character
   */
  public:
  void encryptAES256(const unsigned char* plaintext, int plaintextLength,
                    unsigned char* ciphertext)

  {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if(ctx == nullptr) {
      throw std::runtime_error("Failed to create encryption context");
    }

    if(EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_, nullptr) !=
       1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to initialize encryption context");
    }

    int len;
    int ciphertextLength;

    if(EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintextLength) !=
       1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to encrypt data");
    }
    ciphertextLength = len;

    if(EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to finalize encryption");
    }
    ciphertextLength += len;

    EVP_CIPHER_CTX_free(ctx);
  }

  /**
   * @brief Dencrypts the File using openssl
   * @param ciphertext character pointer of the encrypted character
   * @param ciphertextLength int length of the message
   * @param plaintext character pointer that is to be decrypted
   */
  void decryptAES256(const unsigned char* ciphertext, int ciphertextLength,
                                   unsigned char* plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (ctx == nullptr) {
      throw std::runtime_error("Failed to create decryption context");
    }

           // Use std::unique_ptr to manage memory for plaintextData
    std::unique_ptr<unsigned char[]> plaintextData(new unsigned char[ciphertextLength]);

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_, nullptr) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to initialize decryption context");
    }

    int len;
    int plaintextLength;

    if (EVP_DecryptUpdate(ctx, plaintextData.get(), &len, ciphertext, ciphertextLength) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to decrypt data");
    }
    plaintextLength = len;

    if (EVP_DecryptFinal_ex(ctx, plaintextData.get() + len, &len) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to finalize decryption");
    }
    plaintextLength += len;

           // Copy the decrypted data to the provided plaintext buffer
    std::copy(plaintextData.get(), plaintextData.get() + plaintextLength, plaintext);

    EVP_CIPHER_CTX_free(ctx);


  }

  };
#endif
