#include "loginwindow.h"
#include "include/CryptoPP/secblock.h"
#include "ui_loginwindow.h"
#include <string>

using secure_string = std::basic_string<char, std::char_traits<char>,
                                        CryptoPP::AllocatorWithCleanup<char>>;

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::on_lineEdit_2_returnPressed() {
  std::string username = ui->lineEdit->text().toStdString();
  secure_string password(ui->lineEdit_2->text().toStdString());
  secure_string str("secret");
  // TODO: Add database unlocking code
}

void LoginWindow::on_pushButton_clicked() {
  std::string username = ui->lineEdit->text().toStdString();
  std::string password = ui->lineEdit_2->text().toStdString();
  // TODO: Add database unlocking code
}
