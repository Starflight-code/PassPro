#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Cryptography/CryptographyStorage.h"
#include "Data Storage/DatabaseManager.h"
#include "entryviewer.h"
#include "include/BS_thread_pool.hpp"
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

  private:
  Ui::MainWindow* ui;
  EntryViewer entry;
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* database;

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);
};
#endif // MAINWINDOW_H
