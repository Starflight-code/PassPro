#include "Data_Storage/DatabaseManager.cpp"
#include "Data_Structures/SecureString.cpp"
#include "include/BS_thread_pool.hpp"
#include "loginwindow.h"
#include <thread>

#include <QApplication>

int main(int argc, char* argv[]) {
  /*if(argc == 2 && !strcmp(argv[1], "-test")) {
    std::cout << "Running Test Suite\n";
    Testing::TestSuite testSuite;
    testSuite.runAllTests();
    return 0;
  }*/
  BS::thread_pool pool(3); // Pool has 3 threads, increase if required
  auto func = [&pool]() {
    int y = 1;
  };
  pool.push_task(func);
  DatabaseManager data;
  // data.writeDB(); // uncomment for JSON DB sanitization/desanitization
  // testing
  QApplication a(argc, argv);
  // MainWindow w;
  LoginWindow login;
  // w.show();
  login.show();
  login.tricklePointers(&pool, &data);
  return a.exec();
}
