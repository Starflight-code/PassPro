#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include "Cryptography/Cryptography.cpp"
#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.h"
#include "Data_Storage/DatabaseObject.h"
#include "Data_Structures/PasswordEntry.h"
#include "include/BS_thread_pool.hpp"
#include "ui_entryviewer.h"
#include <QMainWindow>

namespace Ui {
  class EntryViewer;
}

class EntryViewer : public QMainWindow {
  Q_OBJECT

  public:
  explicit EntryViewer(QWidget* parent = nullptr);
  ~EntryViewer();
  void onDatabaseUpdateFinished();

  private slots:
  void on_Close_clicked();

  private slots:
  void on_pushButton_2_clicked();

  private:
  Ui::EntryViewer* ui;
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* data;
  void clearAll();

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);
};

#endif // ENTRYVIEWER_H
