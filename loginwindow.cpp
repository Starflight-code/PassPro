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



  database->readDB(&cryptoStorage);
  if(cryptoStorage.valid){


  this->hide();
  window.refresh();
  window.show();
  }
  else
  {

  messagebox.setWindowTitle("Invalid Login");
  messagebox.setText("Invalid Login: Username already exists");
  messagebox.show();
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
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
