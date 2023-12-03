#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  DatabaseManager databaseManager;
  std::vector<PasswordEntry> entries = databaseManager.getEntries();
  populateTableWidget(std::move(databaseManager.getEntries()));
  // entries, crypto
  //   Cryptography Cryptography();

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

void MainWindow::on_tableWidget_cellClicked(int row, int column) {
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
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString("NAME")));
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.username)));
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.url)));
  }

  // Update and show the table
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->show();
}

void MainWindow::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->database = database;
  entry.tricklePointers(this->userCredentials, this->pool, this->database);
};
