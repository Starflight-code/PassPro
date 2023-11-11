#include "DatabaseManager.cpp"
#include "mainwindow.h"
#include "testing.cpp"

#include <QApplication>

int main(int argc, char* argv[]) {
  if(argc == 2 && !strcmp(argv[1], "-test")) {
    std::cout << "Running Test Suite\n";
    Testing::TestSuite testSuite;
    testSuite.runAllTests();
    return 0;
  }
  DatabaseManager data;
  // data.writeDB(); // uncomment for JSON DB sanitization/desanitization testing
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
