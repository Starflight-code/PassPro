#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Cryptography/Cryptography.cpp"
#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.h"
#include "Data_Storage/DatabaseObject.h"
#include "Data_Structures/PasswordEntry.h" // only in for testing and development
#include "entryviewer.h"
#include "include/BS_thread_pool.hpp"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QStandardItemModel tableContent;

  private slots:
  void on_pushButton_clicked();

  public:
  void populateTableWidget(const std::vector<PasswordEntry>& entries);
  void populateTableWidget(const std::vector<int>& entries);

  private:
  bool searchMode;
  Ui::MainWindow* ui;
  EntryViewer entry;
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* database;
  std::vector<PasswordEntry>* entries;
  std::vector<int> searchDBIndexes;
  QMessageBox messagebox;

  void searchFor(std::string query);
  static std::string trimString(std::string str, char trimChar = ' ');
  static std::string toLowerCase(std::string str);

  private slots:
  void on_tableWidget_cellClicked(int row, int column);
  void on_Logout_clicked();

  void on_lineEdit_returnPressed();

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);
  void refresh();
};
#endif // MAINWINDOW_H
