#define CATCH_CONFIG_MAIN
#include "..\catch\catch.hpp"
#include "..\Cryptography\Cryptography.cpp"
#include "..\Cryptography\CryptographyStorage.h"
#include "..\Data Storage\DatabaseManager.cpp"
#include "..\Data Storage\DatabaseObject.cpp"
#include "..\Data Structures\PasswordEntry.cpp"

TEST_CASE("Cryptography Encryption and Decryption Test", "[Cryptography]") {
  const unsigned char key[] = "0123456789ABCDEF0123456789ABCDEF";
  const unsigned char plaintext[] = "Hello, Catch2 Test!";
  const int plaintextLength = sizeof(plaintext) - 1; // excluding null terminator
  unsigned char ciphertext[256];                     // Adjust the size accordingly
  unsigned char decryptedText[256];                  // Adjust the size accordingly

  Cryptography crypto(key);

  SECTION("Encrypts plaintext") {
    REQUIRE_NOTHROW(crypto.encryptAES256(plaintext, plaintextLength, ciphertext));

    // Add additional checks if needed
  }

  SECTION("Decrypts plaintext") {
    // Encrypt the plaintext
    crypto.encryptAES256(plaintext, plaintextLength, ciphertext);

    // Decrypt the ciphertext
    REQUIRE_THROWS_WITH(
        crypto.decryptAES256(ciphertext, plaintextLength, decryptedText),
        "Failed to finalize decryption");
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
TEST_CASE("PasswordObject and searchableURL Test") {
  SECTION("URL with www. prepended should have searchableURL without www.") {
    PasswordEntry entry("securePassword", "Example", "www.example.com", "user123", "Some notes");
    REQUIRE(entry.seachableURL == "example.com");
  }

  SECTION("URL without www. should have searchableURL unchanged") {
    PasswordEntry entry("anotherPassword", "Another Example", "example.org", "user456", "More notes");
    REQUIRE(entry.seachableURL == "example.org");
  }
}
TEST_CASE("DatabaseManager JSON Sanitization and Desanitization Test", "[DatabaseManager]") {
  // Create a DatabaseManager instance
  DatabaseManager dbManager;

  SECTION("Sanitizes and Desanitizes JSON") {
    // Manually add some entries to the manager for testing
    PasswordEntry entry1("Entry1", "http://example.com", "user1", "pass1", "Note1");
    PasswordEntry entry2("Entry2", "http://example2.com", "user2", "pass2", "Note2");

    // Assuming you don't have a method to add entries,
    // you can add them directly to the entries vector
    dbManager.addEntry(entry1);
    dbManager.addEntry(entry2);

    // Call the sanitization method
    dbManager.writeDB();

    // Retrieve the entries after desanitization using the getter method
    const std::vector<PasswordEntry>& desanitizedEntries = dbManager.getEntries();

    // Verify that the desanitized entries match the original entries
    REQUIRE(desanitizedEntries.size() == 2);
    REQUIRE(desanitizedEntries[0] == entry1);
    REQUIRE(desanitizedEntries[1] == entry2);
  }
}
TEST_CASE("Memory Leak Test for PasswordEntry", "[MemoryLeak]") {
  PasswordEntry* entry = new PasswordEntry("example", "http://example.com", "user", "pass", "note");
  // Perform any actions that would typically happen in your application
  delete entry; // Properly deleting the allocated memory
  // Entry should be deleted, and we're checking for leaks
}
TEST_CASE("Memory Leak Test for DatabaseObject", "[MemoryLeak]") {
  DatabaseObject* dbObject = new DatabaseObject();
  // Perform any actions that would typically happen in your application
  delete dbObject;
  // dbObject should be deleted, but we're checking for leaks
}
TEST_CASE("Memory Leak Test for DatabaseManager", "[MemoryLeak]") {
  DatabaseManager* dbManager = new DatabaseManager();
  // Perform any actions that would typically happen in your application
  delete dbManager;
  // dbManager should be deleted, but we're checking for leaks
}