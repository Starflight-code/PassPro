#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::on_lineEdit_2_returnPressed() {
  std::string username = ui->lineEdit->text().toStdString();
  std::string password = ui->lineEdit_2->text().toStdString();
  // TODO: Add database unlocking code
}

void LoginWindow::on_pushButton_clicked() {
  std::string username = ui->lineEdit->text().toStdString();
  std::string password = ui->lineEdit_2->text().toStdString();
  // TODO: Add database unlocking code
}
