#ifndef CRYPTOGRAPHY_CPP
#define CRYPTOGRAPHY_CPP

// #include "CryptographyStorage.h"
#include "../Data_Structures/SecureString.cpp"
#include <memory>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdexcept>

class Cryptography {
  public:
  Cryptography(const unsigned char* key) : key_(key) {
    OpenSSL_add_all_algorithms();
  }

  Cryptography(DataProcessing::secureString key) {
    OpenSSL_add_all_algorithms();
    keyString = key;
    key_ = (const unsigned char*)keyString.c_str();
  }

  ~Cryptography() {
    EVP_cleanup();
  }

  private:
  DataProcessing::secureString keyString;
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

    if(ctx == nullptr) {
      throw std::runtime_error("Failed to create decryption context");
    }

    // Use std::unique_ptr to manage memory for plaintextData
    std::unique_ptr<unsigned char[]> plaintextData(new unsigned char[ciphertextLength]);

    if(EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_, nullptr) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to initialize decryption context");
    }

    int len;
    int plaintextLength;

    if(EVP_DecryptUpdate(ctx, plaintextData.get(), &len, ciphertext, ciphertextLength) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to decrypt data");
    }
    plaintextLength = len;

    if(EVP_DecryptFinal_ex(ctx, plaintextData.get() + len, &len) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      throw std::runtime_error("Failed to finalize decryption");
    }
    plaintextLength += len;

    // Copy the decrypted data to the provided plaintext buffer
    std::copy(plaintextData.get(), plaintextData.get() + plaintextLength, plaintext);

    EVP_CIPHER_CTX_free(ctx);
  }

  /**
   * @brief Encrypts a string using the key in this instance (added upon construction)
   * @param string a DataProcesssing::secureString to encrypt
   * @return a encrypted DataProcessing::secureString
   */
  DataProcessing::secureString encrypt(DataProcessing::secureString string) {
    int length = string.length();
    int outputLength = length + 16 - (length % 16);
    unsigned char* stringToEncrypt = (unsigned char*)string.c_str();
    unsigned char* outputString = (unsigned char*)malloc(outputLength);

    encryptAES256(stringToEncrypt, length, outputString);

    return DataProcessing::secureString((const char*)outputString, outputLength);
    /*char tempString[outputLength + 1];
    memcpy(tempString, outputString, outputLength);
    tempString[outputLength - 1] = '\0';*/

    // return DataProcessing::secureString(tempString);
  }

  /**
   * @brief Decrypts a string using the key in this instance (added upon construction)
   * @param string a DataProcesssing::secureString to decrypt
   * @return a decrypted DataProcessing::secureString
   */
  DataProcessing::secureString decrypt(DataProcessing::secureString string) {
    int length = string.length();
    unsigned char* stringToDecrypt = (unsigned char*)string.c_str();
    unsigned char* outputString = (unsigned char*)malloc(length);

    decryptAES256(stringToDecrypt, length, outputString);
    DataProcessing::secureString returnString((const char*)outputString, length);
    returnString = fixOutput(returnString);
    return returnString;

    /*char tempString[length + 1];
    memcpy(tempString, outputString, length);
    tempString[length - 1] = '\0';

    return DataProcessing::secureString(tempString);*/
  }

  /**
   * @brief Removes unnecessary data added to the end of the string during formatting
   * @param string the string to process, removing extra '\000' characters
   * @return DataProcessing::secureString without extra characters
   */
  DataProcessing::secureString fixOutput(DataProcessing::secureString string) {
    while(string[string.length() - 1] == '\000' && string[string.length() - 2] == '\000') {
      string = string.substr(0, string.length() - 2);
    }

    return string;
  }
};
#endif
