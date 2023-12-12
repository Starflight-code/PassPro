#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::submit() {
  std::string username = ui->lineEdit->text().toStdString();
  DataProcessing::secureString password(ui->lineEdit_2->text().toStdString());

  cryptoStorage = CryptographyStorage(username, password);
  window.tricklePointers(&cryptoStorage, pool, database);

  this->hide();

  try {
    database->readDB(&cryptoStorage);
    window.refresh();
    window.show();
  } catch(...) {
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

void LoginWindow::on_togglePassword_clicked() {
  bool currentVisibility = ui->lineEdit_2->echoMode() != QLineEdit::Password;
  ui->lineEdit_2->setEchoMode(currentVisibility ? QLineEdit::Password : QLineEdit::Normal);
}

