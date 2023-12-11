#include "entryviewer.h"

DatabaseManager databaseManager;

/*class DatabaseUpdateThread : public QThread {
public:
  void run() override { updateDatabase(); }
};*/

EntryViewer::EntryViewer(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::EntryViewer) {
  ui->setupUi(this);
  updateCell = -1;

  // connect(ui->pushButton_2, &QPushButton::clicked, this,
  //         &EntryViewer::on_pushButton_2_clicked);
  // connect(ui->Password, &QLineEdit::editingFinished, this,
  //         &EntryViewer::on_Password_editingFinished);
}

EntryViewer::~EntryViewer() { delete ui; }

void EntryViewer::on_Close_clicked() {
  clearAll();
  hide();
}

void EntryViewer::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database, QTableWidget* table) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->data = database;
  this->mainTable = table;
  this->entries = data->getEntries();
};

void EntryViewer::clearAll() {
  ui->Password->setText("");
  ui->Name->setText("");
  ui->URL->setText("");
  ui->Username->setText("");
  ui->Notes->setText("");
}

void EntryViewer::refreshTable() {
  mainTable->clearContents();

  // Set table headers
  QStringList headers({"Name", "Username", "URL"});
  mainTable->setHorizontalHeaderLabels(headers);

  // Set number of rows and columns
  std::vector<PasswordEntry>* entries = data->getEntries();
  mainTable->setRowCount(entries->size());
  mainTable->setColumnCount(3);

  // Populate each cell with corresponding data
  for(int row = 0; row < entries->size(); ++row) {
    const PasswordEntry& entry = entries->at(row);
    mainTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.name)));
    mainTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(entry.username)));
    mainTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(entry.url)));
  }

  // Update and show the table
  mainTable->resizeColumnsToContents();
  mainTable->show();
  mainTable->update();
}

void EntryViewer::setPasswordText(const QString& text) {
  ui->Password->setText(text);
}

void EntryViewer::setNameText(const QString& text) {
  ui->Name->setText(text);
}

void EntryViewer::setURLText(const QString& text) {
  ui->URL->setText(text);
}

void EntryViewer::setUsernameText(const QString& text) {
  ui->Username->setText(text);
}

void EntryViewer::setNotesText(const QString& text) {
  ui->Notes->setText(text);
}

void EntryViewer::on_ApplyAndClose_clicked() {

  if(updateCell == -1) {

    data->addEntry(PasswordEntry(
        ui->Password->text().toStdString(), ui->Name->text().toStdString(),
        ui->URL->text().toStdString(), ui->Username->text().toStdString(),
        ui->Notes->text().toStdString()));
  } else {
    entries->at(updateCell) = PasswordEntry(
        ui->Password->text().toStdString(), ui->Name->text().toStdString(),
        ui->URL->text().toStdString(), ui->Username->text().toStdString(),
        ui->Notes->text().toStdString());
    updateCell = -1;
  }
  auto saveTask = [](DatabaseManager* data, CryptographyStorage* credentials) {
    data->writeDB(credentials);
  };

  pool->push_task(saveTask, data, userCredentials);

  refreshTable();

  clearAll();
  hide();
}

void EntryViewer::on_Delete_clicked() {
  hide();
  if(updateCell == -1) {
    return;
  } else {
    entries->erase(entries->begin() + updateCell);
    refreshTable();
    auto saveTask = [](DatabaseManager* data, CryptographyStorage* credentials) {
      data->writeDB(credentials);
    };

    pool->push_task(saveTask, data, userCredentials);
  }
}

/**
 * @brief EntryViewer::runClipboardUIAndClear clears the clipboard after 20 seconds and changes the button text for 3 seconds
 * @param button that will have its textasdaasda changed
 */
void EntryViewer::runClipboardUIAndClear(QToolButton* button) {
  auto sleepFor = [](int seconds) { // converts usleep input to seconds vs microseconds (default)
    usleep(seconds * 1000000);
  };
  button->setText(QString("✅"));
  sleepFor(3);
  button->setText(QString("📋"));
  sleepFor(17);
  clipboardxx::clipboard clipboard;
  clipboard << "";
}

void EntryViewer::on_passwordCopyBtn_clicked() {
  clipboardxx::clipboard clipboard;
  clipboard.copy(ui->Password->text().toStdString());
  auto clipboardTask = [](Ui::EntryViewer* ui) {
    runClipboardUIAndClear(ui->passwordCopyBtn);
  };
  pool->push_task(clipboardTask, ui);
}

void EntryViewer::on_urlCopyBtn_clicked() {
  clipboardxx::clipboard clipboard;
  clipboard.copy(ui->URL->text().toStdString());
  auto clipboardTask = [](Ui::EntryViewer* ui) {
    runClipboardUIAndClear(ui->urlCopyBtn);
  };
  pool->push_task(clipboardTask, ui);
}

void EntryViewer::on_usernameCopyBtn_clicked() {
  clipboardxx::clipboard clipboard;
  clipboard.copy(ui->Username->text().toStdString());
  auto clipboardTask = [](Ui::EntryViewer* ui) {
    runClipboardUIAndClear(ui->usernameCopyBtn);
  };
  pool->push_task(clipboardTask, ui);
}
