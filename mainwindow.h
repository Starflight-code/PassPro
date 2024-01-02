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
#include <QMessageBox>
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

  public:
  /**
   * @brief populates the UI table using a vector of entries
   * @param entires a std::vector<PasswordEntry> containing entries to fill the table with
   */
  void populateTableWidget(const std::vector<PasswordEntry>& entries);

  /**
   * @brief populates the UI table using a vector of indexes, looked up with in class entries vector. (Search Mode)
   * @param entries a std::vector<int> of indexes to values within entries (in class) vector pointer.
   */
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

  /**
   * @brief searches for the string to match the beginning of entry names, searchableURLs and usernames
   * @param query string to search with
   */
  void searchFor(std::string query);

  /**
   * @brief trims all leading and following characters (of trimChar) from a string
   * @param str the string to trim
   * @param trimChar the character to trim from the beginnning and end
   * @return a string with continuous sets of leading and following character matching trimChar removed
   */
  static std::string trimString(std::string str, char trimChar = ' ');

  /**
   * @brief converts all characters in a string to lowercase variants, does not support unicode
   * @param str the string to convert
   * @return a string with all lowercase characters
   */
  static std::string toLowerCase(std::string str);

  private slots:

  /**
   * @brief handles the newEntry button press event. Opens the entryUI for entry creation.
   */
  void on_newEntry_clicked();

  /**
   * @brief handles the tableWidget clicked event. Opens the entryUI for entry editing.
   */
  void on_tableWidget_cellClicked(int row, int column);

  /**
   * @brief handles the logout button press event. Exits with code 0.
   */
  void on_Logout_clicked();

  /**
   * @brief handles the return key press while search bar is active. Enables search mode and displays results.
   */
  void on_searchBar_returnPressed();

  public:
  /**
   * @brief Adds pointers from higher level classes, allows interaction with shared resources
   * @param userCredentials a pointer to CryptographyStorage object
   * @param pool a pointer to an initialized BS::thread_pool instance
   * @param database a pointer to a DatabaseManager object
   */
  void tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database);

  /**
   * @brief refreshes the table to display new information from the DB.
   */
  void refresh();
};
#endif // MAINWINDOW_H
