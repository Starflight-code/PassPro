#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);
}

LoginWindow::~LoginWindow() { delete ui; }

void LoginWindow::submit() {
  std::string username = ui->username->text().toStdString();
  DataProcessing::secureString password(ui->password->text().toStdString());

  cryptoStorage = CryptographyStorage(username, password);
  window.tricklePointers(&cryptoStorage, pool, database);

  database->readDB(&cryptoStorage);
  if(cryptoStorage.status == cryptoStorage.valid) {

    this->hide();
    window.refresh();
    window.show();
  } else if(cryptoStorage.status == cryptoStorage.noFile) {
    messagebox.setWindowTitle("Registration");
    messagebox.setText("This username does not exist, continuing will result in a new user. ");
    messagebox.show();
    this->hide();
    window.refresh();
    window.show();
  } else {

    messagebox.setWindowTitle("Invalid Login");
    messagebox.setText("Invalid Login: Username already exists");
    messagebox.show();
    ui->username->clear();
    ui->password->clear();
  }
}

void LoginWindow::on_password_returnPressed() {
  submit();
}

void LoginWindow::on_submitButton_clicked() {
  submit();
}

void LoginWindow::tricklePointers(BS::thread_pool* pool, DatabaseManager* database) {
  this->pool = pool;
  this->database = database;
};

void LoginWindow::on_togglePassword_clicked() {
  bool currentVisibility = ui->password->echoMode() != QLineEdit::Password;
  ui->password->setEchoMode(currentVisibility ? QLineEdit::Password : QLineEdit::Normal);
}
