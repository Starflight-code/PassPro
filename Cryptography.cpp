#include "CryptographyStorage.cpp"
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdexcept>

class Cryptography {
  // CryptographyStorage credManager;
  //  https://friendlyuser.github.io/posts/tech/cpp/Using_OpenSSL_in_C++_A_Comprehensive_Guide/

public:
  Cryptography(const unsigned char *key) : key_(key) {
    // Initialize OpenSSL library
    OpenSSL_add_all_algorithms();
    // ERR_load_crypto_strings();
  }

  ~Cryptography() {
    // Cleanup OpenSSL
    EVP_cleanup();
    // ERR_free_strings();
  }

  void encryptAES256(const unsigned char *plaintext, int plaintextLength,
                     unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (ctx == nullptr) {
      throw std::runtime_error("Failed to create encryption context");
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_, nullptr) !=
        1) {
      throw std::runtime_error("Failed to initialize encryption context");
    }

    int len;
    int ciphertextLength;

    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintextLength) !=
        1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to encrypt data");
    }
    ciphertextLength = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to finalize encryption");
    }
    ciphertextLength += len;

    EVP_CIPHER_CTX_free(ctx);
  }

private:
  const unsigned char *key_;
};
