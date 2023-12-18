#define CATCH_CONFIG_MAIN
#include "../Cryptography/Cryptography.cpp"
#include "../Cryptography/CryptographyStorage.h"
#include "../Data_Storage/DatabaseManager.h"
#include "../Data_Storage/DatabaseManager.cpp"
#include "../Data_Storage/DatabaseObject.h"
#include "../Data_Structures/PasswordEntry.h"
// #include "Cryptography.h"
#include "../include/catch.hpp"

TEST_CASE("Cryptography - Encryption and Decryption", "[Cryptography]") {
  // Create a Cryptography instance with a sample key
  DataProcessing::secureString key = "sample_key";
  Cryptography crypto(key);

  SECTION("Encryption and Decryption of a string") {
    DataProcessing::secureString originalString = "Hello, Catch2!";

    // Encrypt the original string
    DataProcessing::secureString encryptedString = crypto.encrypt(originalString);

           // Decrypt the encrypted string
    DataProcessing::secureString decryptedString = crypto.decrypt(encryptedString);

           // Verify that the decrypted string matches the original string
    REQUIRE(decryptedString == originalString);
  }

         // Add more test cases as needed
}

TEST_CASE("CryptographyStorage - Constructor with parameters", "[CryptographyStorage]") {
  // Test the constructor with parameters
  std::string username = "test_user";
  DataProcessing::secureString password = "test_password";
  CryptographyStorage storage(username, password);

         // Verify that the username and password are set correctly
  REQUIRE(storage.user == username);
  REQUIRE(storage.key == password);
}

TEST_CASE("CryptographyStorage - Default Constructor", "[CryptographyStorage]") {
  // Test the default constructor
  CryptographyStorage storage;

         // Verify that the username is empty and the password is an empty secureString
  REQUIRE(storage.user.empty());
  REQUIRE(storage.key.empty());
}
TEST_CASE("PasswordObject and searchableURL Test") {
  SECTION("URL with www. prepended should have searchableURL without www.") {
    PasswordEntry entry("securePassword", "Example", "www.example.com", "user123", "Some notes");
    REQUIRE(entry.searchableURL == "example.com");
  }

  SECTION("URL without www. should have searchableURL unchanged") {
    PasswordEntry entry("anotherPassword", "Another Example", "example.org", "user456", "More notes");
    REQUIRE(entry.searchableURL == "example.org");
  }
}
TEST_CASE("DatabaseManager - sanitizeJSON and desanitizeJSON", "[DatabaseManager]") {
  // Create a DatabaseManager instance
  DatabaseManager dbManager;
  DatabaseObject db;

         // Create sample entries
  PasswordEntry entry1("pass1", "name1", "url1", "user1", "note1", "s_url1");
  PasswordEntry entry2("pass2", "name2", "url2", "user2", "note2", "s_url2");

         // Add sample entries to the manager
  db.addEntry(entry1);
  db.addEntry(entry2);

         // Test sanitizeJSON
  nlohmann::json sanitizedJson = dbManager.sanitizeJSON();

         // Verify the structure of the sanitized JSON
  REQUIRE(sanitizedJson["names"][0] == "name1");
  REQUIRE(sanitizedJson["names"][1] == "name2");
  REQUIRE(sanitizedJson["urls"][0] == "url1");
  REQUIRE(sanitizedJson["urls"][1] == "url2");
  // Add more checks based on your data structure

         // Test desanitizeJSON
  dbManager.desanitizeJSON(sanitizedJson);

         // Verify that the entries in the manager match the original entries
  REQUIRE(dbManager.getEntries()->at(0) == entry1);
  REQUIRE(dbManager.getEntries()->at(1) == entry2);
  // Add more checks based on your data structure
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
