#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  entry.ui->Delete->hide();
  entry.show();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column) {
  const PasswordEntry entryObject = entries->at(row);
  entry.setPasswordText(QString::fromStdString(entryObject.password));
  entry.setNameText(QString::fromStdString(entryObject.name));
  entry.setURLText(QString::fromStdString(entryObject.url));
  entry.setUsernameText(QString::fromStdString(entryObject.username));
  entry.setNotesText(QString::fromStdString(entryObject.notes));
  entry.updateCell = row;
  entry.ui->Delete->show();
  entry.show();
}

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
  this->entries = database->getEntries();
  entry.tricklePointers(this->userCredentials, this->pool, this->database, ui->tableWidget);
  refresh();
};

void MainWindow::refresh() {
  populateTableWidget(*database->getEntries());
}

void MainWindow::on_Logout_clicked() {
  exit(0);
}
