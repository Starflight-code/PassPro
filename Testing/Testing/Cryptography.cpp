#include "Cryptography.h"
#include "CryptographyStorage.h"
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

  void encryptAES256(const unsigned char* plaintext, int plaintextLength,
                     unsigned char* ciphertext) {
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

  void decryptAES256(const unsigned char* ciphertext, int ciphertextLength,
                     unsigned char* plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if(ctx == nullptr) {
      throw std::runtime_error("Failed to create decryption context");
    }

    if(EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_, nullptr) !=
       1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to initialize decryption context");
    }

    int len;
    int plaintextLength;

    if(EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertextLength) !=
       1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to decrypt data");
    }
    plaintextLength = len;

    if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to finalize decryption");
    }
    plaintextLength += len;

    EVP_CIPHER_CTX_free(ctx);
  }

  private:
  const unsigned char* key_;
};
