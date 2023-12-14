#include "Data_Storage/DatabaseManager.cpp"
#include "Data_Structures/SecureString.cpp"
#include "include/BS_thread_pool.hpp"
#include "loginwindow.h"
#include "testing.cpp"
#include <thread>

#include <QApplication>

int main(int argc, char* argv[]) {
  const bool testMode = false;
  if(argc == 2 && !strcmp(argv[1], "-test") || testMode == true) {
    std::cout << "Running Test Suite\n";
    Testing::TestSuite testSuite;
    testSuite.runAllTests();
    return 0;
  }
  BS::thread_pool pool(6); // Pool has 6 threads, increase if required

  DatabaseManager data;
  QApplication a(argc, argv);
  LoginWindow login;

  login.show();
  login.tricklePointers(&pool, &data);
  return a.exec();
}
