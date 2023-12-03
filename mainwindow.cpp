#include "mainwindow.h"
#include "Data_Storage/DatabaseManager.h"
#include "ui_mainwindow.h"
#include "Data_Storage/DatabaseObject.h" // Include the header for your DatabaseObject class
#include "Cryptography/Cryptography.cpp"  // Include the header for your Cryptography class

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //  Cryptography Cryptography();

           // Fetch data from the database (assuming you have appropriate methods in your DatabaseObject class)
           // This is a simplified example, replace it with your actual logic
    // QList<PasswordEntry> entries = databaseManager.getEntries();

           // Populate the QTableWidget with decrypted data
    // populateTableWidget(entries, crypto);
  }


  MainWindow::~MainWindow() {
    delete ui;
  }

  void MainWindow::on_pushButton_clicked() {
    entry.show();
  }

  void MainWindow::on_tableWidget_cellClicked(int row, int column)
  {
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


void MainWindow::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->database = database;
  entry.tricklePointers(this->userCredentials, this->pool, this->database);
};
