#include "DatabaseManager.cpp"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    DatabaseManager data;
    // data.writeDB(); // uncomment for JSON DB sanitization/desanitization testing
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
