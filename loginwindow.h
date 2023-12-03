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

namespace Ui {
  class LoginWindow;
}

class LoginWindow : public QMainWindow {
  Q_OBJECT

  public:
  explicit LoginWindow(QWidget* parent = nullptr);
  ~LoginWindow();
  // using secure_string = std::basic_string<char, std::char_traits<char>,
  //                                         CryptoPP::AllocatorWithCleanup<char>>;
  std::string username;
  // secure_string password;

  private slots:
  void on_lineEdit_2_returnPressed();

  void on_pushButton_clicked();

  private:
  void submit();

  Ui::LoginWindow* ui;
  CryptographyStorage* userCredentials;
  MainWindow window;
  BS::thread_pool* pool;
  DatabaseManager* database;

  public:
  void tricklePointers(BS::thread_pool* pool, DatabaseManager* database);
};

#endif // LOGINWINDOW_H
