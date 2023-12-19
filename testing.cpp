#undef assert // somehow this is defined elsewhere

#include "Cryptography/Cryptography.cpp"
#include "Cryptography/CryptographyStorage.h"
#include "Data_Structures/PasswordEntry.h"
#include "Data_Structures/SecureString.cpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace Testing {

  class UnitTester {
    struct completedTest {
      std::string testName;
      bool testResult;
      completedTest(std::string testName, bool testResult) {
        this->testName = testName;
        this->testResult = testResult;
      }
    };
    std::vector<completedTest> testOutput;

public:
    void assert(std::string testName, bool assertion) {
      if(assertion) {
        testOutput.push_back(completedTest(testName, assertion));
      } else {
        testOutput.push_back(completedTest(testName, assertion));
      }
    }

    void finished() {
      bool testStatus = true;
      std::vector<std::string> failedTests;
      for(int i = 0; i < testOutput.size(); i++) {
        std::string conditional = testOutput[i].testResult ? "Passed (✅)" : "Failed (❌)";
        testStatus = testStatus ? testOutput[i].testResult : testStatus; // checks if all tests have passed
        if(!testOutput[i].testResult) {
          failedTests.push_back("Index " + std::to_string(i) + " | " + testOutput[i].testName + ": " + conditional + "\n");
        }
      }
      if(testStatus) {
        std::cout << "\nAll tests have passed! (" + std::to_string(testOutput.size()) + " ✅)\n";
        exit(0);
      } else {
        for(int i = 0; i < failedTests.size(); i++) {
          std::cout << failedTests.at(i);
        }
        std::cout << "\n\n" + std::to_string(failedTests.size()) + '/' + std::to_string(testOutput.size()) + " tests have failed! (❌)\n";
        exit(1);
      }
    }
  };

  class TestSuite {
public:
    void encryptionTest(UnitTester* unit) {

      DataProcessing::secureString key = "0123456789ABCDEF0123456789ABCDEF";
      DataProcessing::secureString text = "Hello, Catch2 Test!";

      Cryptography crypto = Cryptography(key);
      bool fail;
      try {
        crypto.encrypt(text);
        fail = false;
      } catch(...) {
        fail = true;
      }
      unit->assert("Encryption: No Throw", fail == false);
    }

    void decryptionTest(UnitTester* unit) {
      DataProcessing::secureString key = "0123456789ABCDEF0123456789ABCDEF";
      DataProcessing::secureString text = "Hello, Catch2 Test!";
      DataProcessing::secureString encryptedText;
      DataProcessing::secureString decryptedText;

      Cryptography crypto = Cryptography(key);
      encryptedText = crypto.encrypt(text);
      decryptedText = crypto.decrypt(encryptedText);
      bool equal = true;
      for(int i = 0; i < decryptedText.length(); i++) {
        equal = equal ? decryptedText[i] == text[i] : false; // keep equal state if equal is false, otherwise set equal depending
                                                             // on whether the two characters at index i are equal
      }
      unit->assert("Decryption: Must Be Equal", equal);
    }

    void cryptographyStorageConstructor(UnitTester* unit) {
      std::string testUser = "testUser";
      DataProcessing::secureString testPassword = "testPassword";

      CryptographyStorage storage(testUser, testPassword);

      unit->assert("CryptographyStorage: Username Constructor", storage.user == testUser);
      unit->assert("CryptographyStorage: Password Constructor", storage.key == testPassword);
    }

    void searchableURL(UnitTester* unit) {
      PasswordEntry entry("securePassword", "Example", "www.example.com", "user123", "Some notes");
      unit->assert("SearchableURL 1", entry.searchableURL == "example.com");

      PasswordEntry entry2("anotherPassword", "Another Example", "example.org", "user456", "More notes");
      unit->assert("SearchableURL 2", entry2.searchableURL == "example.org");
    }

    void runAllTests() {
      UnitTester unit;
      encryptionTest(&unit);
      decryptionTest(&unit);
      cryptographyStorageConstructor(&unit);
      searchableURL(&unit);
      unit.finished();
    }
  };
}