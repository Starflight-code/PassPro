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
  DatabaseObject dbo;
  PasswordEntry entry("password", "name", " url", "username", "notes");
  PasswordEntry entry2("password2", "name2", " url2", "username2", "notes2");
  // dbo.addEntry(entry);
  // dbo.addEntry(entry2);
  BS::thread_pool pool(3); // Pool has 3 threads, increase if required
  auto func = []() {
    int y = 1;
  };
  // pool.push_task(func);
  DatabaseManager data;
  // data.writeDB(); // uncomment for JSON DB sanitization/desanitization
  // testing

  // Cryptography crypto((unsigned char*)DataProcessing::secureString("key").c_str());
  // DataProcessing::secureString output = crypto.encrypt(DataProcessing::secureString("This is the input data for an AES-256 Cypher!"));
  // output = crypto.decrypt(output);
  QApplication a(argc, argv);
  // MainWindow w;
  LoginWindow login;
  // w.show();
  login.show();
  login.tricklePointers(&pool, &data);
  return a.exec();
}
