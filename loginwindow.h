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
#include <QMessageBox>
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

  private slots:

  /**
   * @brief handles the returnKeyPressed event when password line is active. Initiates a login.
   */
  void on_password_returnPressed();

  /**
   * @brief handles the submitButton press event. Initiates a login.
   */
  void on_submitButton_clicked();

  /**
   * @brief handles the togglePassword button press event. Shows/hides the password.
   */
  void on_togglePassword_clicked();

  private:
  /**
   * @brief logs in by requesting DB import from the selected encrypted file or creating a new user.
   */
  void submit();

  Ui::LoginWindow* ui;
  CryptographyStorage* userCredentials;
  MainWindow window;
  BS::thread_pool* pool;
  DatabaseManager* database;
  CryptographyStorage cryptoStorage;
  QMessageBox messagebox;

  public:
  /**
   * @brief Adds pointers from higher level classes, allows interaction with shared resources
   * @param pool a pointer to an initialized BS::thread_pool instance
   * @param database a pointer to a DatabaseManager object
   */
  void tricklePointers(BS::thread_pool* pool, DatabaseManager* database);
};

#endif // LOGINWINDOW_H
