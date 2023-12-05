#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.cpp"
#include "Data_Structures/PasswordEntry.h"
#include "include/BS_thread_pool.hpp"
#include "ui_entryviewer.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QtWidgets/QTableWidget>

namespace Ui {
  class EntryViewer;
}

class EntryViewer : public QMainWindow {
  Q_OBJECT

  public:
  explicit EntryViewer(QWidget* parent = nullptr);
  ~EntryViewer();
  int updateCell;
  Ui::EntryViewer* ui;

  private slots:
  void on_Close_clicked();
  void on_ApplyAndClose_clicked();

  void on_Delete_clicked();

  private:
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* data;
  QTableWidget* mainTable;
  std::vector<PasswordEntry>* entries;

  void clearAll();
  void refreshTable();

  public:
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database, QTableWidget* table);
  void setPasswordText(const QString& text);
  void setNameText(const QString& text);
  void setURLText(const QString& text);
  void setUsernameText(const QString& text);
  void setNotesText(const QString& text);
};

#endif // ENTRYVIEWER_H
