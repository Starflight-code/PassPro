#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

// #include "include/CryptoPP/secblock.h"
#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.h"
#include "Data_Structures/SecureString.cpp"
#include "include/BS_thread_pool.hpp"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include <QMainWindow>
#include <iostream>
#include <string>
#include <QMessageBox>

namespace Ui {
  class LoginWindow;
}

class LoginWindow : public QMainWindow {
  Q_OBJECT

  public:
  explicit LoginWindow(QWidget* parent = nullptr);
  ~LoginWindow();

  private slots:
  void on_lineEdit_2_returnPressed();

  void on_pushButton_clicked();

  void on_togglePassword_clicked();

  private:
  void submit();

  Ui::LoginWindow* ui;
  CryptographyStorage* userCredentials;
  MainWindow window;
  BS::thread_pool* pool;
  DatabaseManager* database;
  CryptographyStorage cryptoStorage;
  QMessageBox messagebox;

  public:
  void tricklePointers(BS::thread_pool* pool, DatabaseManager* database);
};

#endif // LOGINWINDOW_H
