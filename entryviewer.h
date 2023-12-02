#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include "Cryptography/CryptographyStorage.h"
#include "Data Storage/DatabaseManager.h"
#include "include/BS_thread_pool.hpp"
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
  DatabaseManager* database;

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);
};

#endif // ENTRYVIEWER_H
