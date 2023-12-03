#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.cpp"
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
  MainWindow* mainWindow;
  void clearAll();

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database, MainWindow* window);
  void setPasswordText(const QString& text);
  void setNameText(const QString& text);
  void setURLText(const QString& text);
  void setUsernameText(const QString& text);
  void setNotesText(const QString& text);
};

#endif // ENTRYVIEWER_H
