#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Cryptography/Cryptography.cpp" // Include the header for your Cryptography class
#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.h"
#include "Data_Storage/DatabaseObject.h" // Include the header for your DatabaseObject class
#include "entryviewer.h"
#include "include/BS_thread_pool.hpp"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QStandardItemModel>

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
  private:
  Ui::MainWindow* ui;
  EntryViewer entry;
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* database;
  private slots:
  void on_tableWidget_cellClicked(int row, int column);


  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);
};
#endif // MAINWINDOW_H
