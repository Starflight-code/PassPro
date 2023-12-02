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

void LoginWindow::on_lineEdit_2_returnPressed() {
  username = ui->lineEdit->text().toStdString();
  // secure_string password(ui->lineEdit_2->text().toStdString());
  //  TODO: Add database unlocking code
  DataProcessing::secureString password(ui->lineEdit_2->text().toStdString());
  this->hide();
  window.show();
}

void LoginWindow::on_pushButton_clicked() {
  username = ui->lineEdit->text().toStdString();
  // secure_string password(ui->lineEdit_2->text().toStdString());
  //  TODO: Add database unlocking code
  DataProcessing::secureString password(ui->lineEdit_2->text().toStdString());
  this->hide();
  window.show();
}
