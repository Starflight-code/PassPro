#include "entryviewer.h"
#include "ui_entryviewer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Cryptography/Cryptography.cpp"
#include "Data_Storage/DatabaseManager.h"
#include "Data_Storage/DatabaseObject.h"
#include "Data_Structures/PasswordEntry.h"

DatabaseManager databaseManager;

/*class DatabaseUpdateThread : public QThread {
public:
  void run() override { updateDatabase(); }
};*/

EntryViewer::EntryViewer(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::EntryViewer) {
  ui->setupUi(this);

  // connect(ui->pushButton_2, &QPushButton::clicked, this,
  //         &EntryViewer::on_pushButton_2_clicked);
  // connect(ui->Password, &QLineEdit::editingFinished, this,
  //         &EntryViewer::on_Password_editingFinished);
}

EntryViewer::~EntryViewer() { delete ui; }

DatabaseObject databaseObject;
void EntryViewer::on_pushButton_2_clicked() {
  // Create a PasswordEntry object
  PasswordEntry newEntry(
      ui->Password->text().toStdString(), ui->Name->text().toStdString(),
      ui->URL->text().toStdString(), ui->Username->text().toStdString(),
      ui->Notes->text().toStdString());

         // Add the entry to the DatabaseObject
  databaseObject.addEntry(newEntry);

         // Sanitize the DatabaseObject
  //nlohmann::json sanitizedData = databaseManager.sanitizeJSON();

         // Convert the JSON to a string
  //std::string jsonString = sanitizedData.dump();

         // Assuming you have an instance of your Cryptography class named 'crypto'
  //Cryptography crypto;

         // Encrypt the JSON string
  //std::string encryptedString = crypto.encryptAES256(jsonString);

         // Assuming you have a method to update the UI after the database is updated
  onDatabaseUpdateFinished();

         // Clear all fields and close the window
  clearAll();
  close();
}

void EntryViewer::onDatabaseUpdateFinished() { update(); }

void EntryViewer::on_Close_clicked() {
  clearAll();
  close(); }

void EntryViewer::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->database = database;
};

void EntryViewer::clearAll()
{
  ui->Password->setText("");
  ui->Name->setText("");
  ui->URL->setText("");
  ui->Username->setText("");
  ui->Notes->setText("");
}
