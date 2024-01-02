#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include "Cryptography/CryptographyStorage.h"
#include "Data_Storage/DatabaseManager.cpp"
#include "Data_Structures/PasswordEntry.h"
#include "include/BS_thread_pool.hpp"
#include "include/ClipboardXX/include/clipboardxx.hpp"
#include "ui_entryviewer.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QtWidgets/QTableWidget>
#include <unistd.h>

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

  /**
   * @brief handles on close button press event, clears UI boxes and hides UI
   */
  void on_Close_clicked();

  /**
   * @brief handles the on ApplyAndClose button press event, updates the DB with data from this UI
   */
  void on_ApplyAndClose_clicked();

  /**
   * @brief handles the on Delete button press event. Removes the entry from the DB.
   */
  void on_Delete_clicked();

  /**
   * @brief handles the PasswordCopy button press event. Copies the password to clipboard, clears after 20 seconds.
   */
  void on_passwordCopyBtn_clicked();

  /**
   * @brief handles the urlCopy button press event. Copies the URL to clipboard, clears after 20 seconds.
   */
  void on_urlCopyBtn_clicked();

  /**
   * @brief handles the UsernameCopy button event. Copies the username to clipboard, clears after 20 seconds.
   */
  void on_usernameCopyBtn_clicked();

  private:
  CryptographyStorage* userCredentials;
  BS::thread_pool* pool;
  DatabaseManager* data;
  QTableWidget* mainTable;
  std::vector<PasswordEntry>* entries;
  bool* searchMode;
  std::vector<int>* searchDBIndexes;

  static void runClipboardUIAndClear(QToolButton* button);
  void clearAll();
  void refreshTable();

  public:
  /**
   * @brief Adds pointers from higher level classes, allows interaction with shared resources
   * @param userCredentials a pointer to CryptographyStorage object
   * @param pool a pointer to an initialized BS::thread_pool instance
   * @param database a pointer to a DatabaseManager object
   * @param table a pointer to the QWidgetTable of the MainWindow UI
   * @param searchMode a pointer to a boolean value, specifies if the UI is diplaying search results
   * @param searchDBIndexes a pointer to a std::vector<int>, showing indexes of search matches
   */
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database, QTableWidget* table, bool* searchMode, std::vector<int>* searchDBIndexes);

  /**
   * @brief Sets the password line to the given text
   * @param text QString to set line value to
   */
  void setPasswordText(const QString& text);

  /**
   * @brief Sets the name line to the given text
   * @param text QString to set line value to
   */
  void setNameText(const QString& text);

  /**
   * @brief Sets the URL line to the given text
   * @param text QString to set line value to
   */
  void setURLText(const QString& text);

  /**
   * @brief Sets the username line to the given text
   * @param text QString to set line value to
   */
  void setUsernameText(const QString& text);

  /**
   * @brief Sets the notes text box to the given text
   * @param text QString to set text box value to
   */
  void setNotesText(const QString& text);
};

#endif // ENTRYVIEWER_H
