#define BOOST_TEST_MODULE Testing
/*#include <boost/test/unit_test.hpp>

#include "Cryptography.cpp"
#include "CryptographyStorage.h"

BOOST_AUTO_TEST_SUITE(CryptographyTestSuite)

BOOST_AUTO_TEST_CASE(EncryptionTest) {
  const unsigned char key[] = "0123456789ABCDEF0123456789ABCDEF";
  const unsigned char plaintext[] = "Hello, Boost Test!";
  const int plaintextLength = sizeof(plaintext) - 1; // excluding null terminator
  unsigned char ciphertext[256];                     // Adjust the size accordingly

  Cryptography crypto(key);

  // Encrypt
  BOOST_CHECK_NO_THROW(crypto.encryptAES256(plaintext, plaintextLength, ciphertext));

  // You may add additional checks based on your specific requirements
}

// Add more test cases as needed

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CryptographyStorageTestSuite)

BOOST_AUTO_TEST_CASE(ConstructorTest) {
  const std::string testUser = "testUser";
  const std::string testPassword = "testPassword";

  CryptographyStorage storage(testUser, testPassword);

  BOOST_CHECK_EQUAL(storage.getUser(), testUser);
  BOOST_CHECK_EQUAL(storage.getKey(), testPassword);
}

// Add more test cases as needed

BOOST_AUTO_TEST_SUITE_END()*/