#include "mainwindow.h"
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  DatabaseManager noPointer;

  // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // DatabaseManager databaseManager;
  //  std::vector<PasswordEntry> entries = databaseManager.getEntries();
  //  populateTableWidget(std::move(databaseManager.getEntries()));
  //   entries, crypto
  //     Cryptography Cryptography();

  // Fetch data from the database (assuming you have appropriate methods in your DatabaseObject class)
  // This is a simplified example, replace it with your actual logic
  // database->addEntry(entry);
  // database->addEntry(entry2);
  // std::vector<PasswordEntry> entries;
  // database->entries.push_back(entry); // database->getEntries();
  // database->entries.push_back(entry2);
  // database->addEntry(&entry2);
  //  Populate the QTableWidget with decrypted data
  //  populateTableWidget(database->entries);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  entry.show();
  //ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString("NAME")));

  PasswordEntry entry("password", "name", " url", "username", "notes");
  // PasswordEntry entry2("password2", "name2", " url2", "username2", "notes2");
  database->addEntry(entry);
  // database->addEntry(entry2);

}

void MainWindow::on_tableWidget_cellClicked(int row, int column) {
  // std::vector<PasswordEntry> entries = database->getEntries();
  const PasswordEntry entryObject = entries.at(row);
  entry.setPasswordText(QString::fromStdString(entryObject.password));
  entry.setNameText(QString::fromStdString(entryObject.name));
  entry.setURLText(QString::fromStdString(entryObject.url));
  entry.setUsernameText(QString::fromStdString(entryObject.username));
  entry.setNotesText(QString::fromStdString(entryObject.notes));
  entry.show();
}

// QStandardItemModel tableContent(2, 2);
// for(int row = 0; row < tableContent.rowCount(); ++row) {
//   for(int column = 0; column < tableContent.columnCount(); ++column) {
//    QStandardItem* item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
//     tableContent.setItem(row, column, item);
//   }
// }
// ui->tableView->setModel(&tableContent);
// ui->tableView->update();
void MainWindow::populateTableWidget(const std::vector<PasswordEntry>& entries) {
  // Clear existing table content
  ui->tableWidget->clearContents();

  // Set table headers
  QStringList headers({"Name", "Username", "URL"});
  ui->tableWidget->setHorizontalHeaderLabels(headers);

  // Set number of rows and columns
  ui->tableWidget->setRowCount(entries.size());
  ui->tableWidget->setColumnCount(3);

  // Populate each cell with corresponding data
  for(int row = 0; row < entries.size(); ++row) {
    const PasswordEntry& entry = entries.at(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.name)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry.username)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(entry.url)));
  }

  // Update and show the table
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->show();
  ui->tableWidget->update();
}

void MainWindow::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->database = database;
  entry.tricklePointers(this->userCredentials, this->pool, this->database);
  refresh();
};

void MainWindow::refresh()
{
 populateTableWidget(*database->getEntries());
}
