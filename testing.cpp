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
    void assert_true(std::string testName, bool assertion) {
      if(assertion) {
        testOutput.push_back(completedTest(testName, assertion));
      } else {
        testOutput.push_back(completedTest(testName, assertion));
      }
    }

    void finished() {
      bool testStatus = true;
      for(int i = 0; i < testOutput.size(); i++) {
        std::string conditional = testOutput[i].testResult ? "Passed (✅)" : "Failed (❌)";
        testStatus = testStatus ? testOutput[i].testResult : testStatus; // checks if all tests have passed
        std::cout << testOutput[i].testName + ": " + conditional + "\n";
      }
      if(testStatus) {
        std::cout << "\nAll tests have passed! (✅)\n";
      } else {
        std::cout << "\nSome tests have failed! (❌)\n";
      }
    }
  };

  class TestSuite {
public:
    void runAllTests() {
      UnitTester unit;
      unit.assert_true("Test1", true);
      unit.finished();
    }
  };
}