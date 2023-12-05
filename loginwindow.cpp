#include "loginwindow.h"

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

  cryptoStorage = CryptographyStorage(username, password);
  this->hide();
  // window.tricklePointers
  window.tricklePointers(&cryptoStorage, pool, database);

  try {
    database->readDB(&cryptoStorage);
    window.refresh();
    window.show();
  } catch (...) {
    window.show();

  }

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
