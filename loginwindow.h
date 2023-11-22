#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

// #include "include/CryptoPP/secblock.h"
#include <QMainWindow>

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
  Ui::LoginWindow* ui;
};

#endif // LOGINWINDOW_H
