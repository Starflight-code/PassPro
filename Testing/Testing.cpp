#define CATCH_CONFIG_MAIN
// #include "C:\Users\evana\source\repos\Testing\Testing\Catch\catch.hpp"
#include "Catch/catch.hpp"
#include "Cryptography.cpp"
#include "CryptographyStorage.h"

TEST_CASE("Cryptography Encryption Test", "[Cryptography]") {
  const unsigned char key[] = "0123456789ABCDEF0123456789ABCDEF";
  const unsigned char plaintext[] = "Hello, Catch2 Test!";
  const int plaintextLength = sizeof(plaintext) - 1; // excluding null terminator
  unsigned char ciphertext[256];                     // Adjust the size accordingly

  Cryptography crypto(key);

  SECTION("Encrypts plaintext") {
    REQUIRE_NOTHROW(crypto.encryptAES256(plaintext, plaintextLength, ciphertext));

    // Add additional checks if needed
  }
}

TEST_CASE("CryptographyStorage Constructor Test", "[CryptographyStorage]") {
  const std::string testUser = "testUser";
  const std::string testPassword = "testPassword";

  CryptographyStorage storage(testUser, testPassword);

  SECTION("Constructor initializes user and key") {
    REQUIRE(storage.getUser() == testUser);
    REQUIRE(storage.getKey() == testPassword);

    // Add additional checks if needed
  }
}