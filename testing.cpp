#undef assert // somehow this is defined elsewhere

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
          failedTests.push_back(testOutput[i].testName + ": " + conditional + "\n");
        }
      }
      if(testStatus) {
        std::cout << "\nAll tests have passed! (" + std::to_string(testOutput.size()) + " ✅)\n";
        exit(0);
      } else {
        for(int i = 0; i < failedTests.size(); i++) {
          std::cout << failedTests.at(i);
        }
        std::cout << "\n\nSome tests have failed! (❌)\n";
        exit(1);
      }
    }
  };

  class TestSuite {
public:
    void runAllTests() {
      UnitTester unit;
      unit.assert("Test1", true);
      unit.finished();
    }
  };
}