#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_newEntry_clicked() {
  entry.ui->Delete->hide();
  entry.show();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column) {
  if(searchMode) {
    const PasswordEntry entryObject = entries->at(searchDBIndexes.at(row));
    entry.setPasswordText(QString::fromStdString(entryObject.password));
    entry.setNameText(QString::fromStdString(entryObject.name));
    entry.setURLText(QString::fromStdString(entryObject.url));
    entry.setUsernameText(QString::fromStdString(entryObject.username));
    entry.setNotesText(QString::fromStdString(entryObject.notes));
    entry.updateCell = row;
    entry.ui->Delete->show();
    entry.show();
  } else {
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
  entry.tricklePointers(this->userCredentials, this->pool, this->database, ui->tableWidget, &searchMode, &searchDBIndexes);
  refresh();
};

void MainWindow::refresh() {
  searchMode = false; // add search mode update to external refresh by entryviewer
  populateTableWidget(*database->getEntries());
}

void MainWindow::on_Logout_clicked() {
  exit(0);
}

void MainWindow::searchFor(std::string query) {
  query = trimString(query);
  query = toLowerCase(query);
  int length = query.length();
  searchDBIndexes.clear();
  for(int i = 0; i < entries->size(); i++) {
    std::string user = entries->at(i).username.substr(0, length);
    std::string name = entries->at(i).name.substr(0, length);
    std::string sURL = entries->at(i).searchableURL.substr(0, length);
    user = toLowerCase(user);
    name = toLowerCase(name);
    sURL = toLowerCase(sURL);
    if(query == user || query == name || query == sURL) {
      searchDBIndexes.push_back(i);
    }
  }
  searchMode = true;
  try {
    populateTableWidget(searchDBIndexes);
  } catch(...) {
    messagebox.setText("404 entry not found");
  }
}

std::string MainWindow::toLowerCase(std::string str) {
  for(int i = 0; i < str.length(); i++) {
    str[i] = (char)tolower(str[i]);
  }
  return str;
}

std::string MainWindow::trimString(std::string str, char trimChar) {
  while(str[0] == trimChar) {
    str = str.substr(1, str.length() - 1); // removes the first character
  }
  while(str[str.length() - 1] == trimChar) {
    str = str.substr(0, str.length() - 1); // removes the last character
  }
  return str;
}

void MainWindow::populateTableWidget(const std::vector<int>& entriesIndex) {
  ui->tableWidget->clear();
  // Clear existing table content
  ui->tableWidget->clearContents();

  // Set table headers
  QStringList headers({"Name", "Username", "URL"});
  ui->tableWidget->setHorizontalHeaderLabels(headers);

  // Set number of rows and columns
  ui->tableWidget->setRowCount(entriesIndex.size());
  ui->tableWidget->setColumnCount(3);

  // Populate each cell with corresponding data based on entriesIndex
  for(int row = 0; row < entriesIndex.size(); ++row) {
    int index = entriesIndex[row];
    const PasswordEntry& entry = entries->at(index);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.name)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry.username)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(entry.url)));
  }

  // Update and show the table
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->show();
  ui->tableWidget->update();
}

void MainWindow::on_searchBar_returnPressed() {
  if(ui->searchBar->text().toStdString() == "") {
    refresh();
    return;
  }
  searchFor(ui->searchBar->text().toStdString());
}
