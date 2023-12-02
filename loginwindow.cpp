#include "loginwindow.h"
// #include "include/CryptoPP/secblock.h"
#include "Data_Structures/SecureString.cpp"
#include "ui_loginwindow.h"
#include <iostream>
#include <string>

// using secure_string = std::basic_string<char, std::char_traits<char>,
//                                         CryptoPP::AllocatorWithCleanup<char>>;

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::submit() {
  username = ui->lineEdit->text().toStdString();
  // secure_string password(ui->lineEdit_2->text().toStdString());
  //  TODO: Add database unlocking code
  DataProcessing::secureString password(ui->lineEdit_2->text().toStdString());

  CryptographyStorage cryptoStorage(username, password);
  this->hide();
  // window.tricklePointers
  window.tricklePointers(&cryptoStorage, pool, database);
  window.show();
}

void LoginWindow::on_lineEdit_2_returnPressed() {
  submit();
}

void LoginWindow::on_pushButton_clicked() {
  submit();
}

void LoginWindow::tricklePointers(BS::thread_pool* pool, DatabaseManager* database) {
  this->pool = pool;
  this->database = database;
};
