#include "entryviewer.h"
#include "ui_entryviewer.h"

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

  PasswordEntry newEntry(
      ui->Password->text().toStdString(), ui->Name->text().toStdString(),
      ui->URL->text().toStdString(), ui->Username->text().toStdString(),
      ui->Notes->text().toStdString());
  const unsigned char exampleKey[] = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
      0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
  Cryptography Cryptography(exampleKey);
  try {
    // Encrypt the new entry data
    unsigned char encryptedName[256];
    unsigned char encryptedUrl[256];
    unsigned char encryptedPassword[256];
    unsigned char encryptedUsername[256];
    unsigned char encryptedNotes[256];
    unsigned char encryptedSearchableURL[256];

    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.name.c_str()),
                               newEntry.name.length(), encryptedName);
    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.url.c_str()),
                               newEntry.url.length(), encryptedUrl);
    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.password.c_str()),
                               newEntry.password.length(), encryptedPassword);
    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.username.c_str()),
                               newEntry.username.length(), encryptedUsername);
    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.notes.c_str()),
                               newEntry.notes.length(), encryptedNotes);
    Cryptography.encryptAES256(reinterpret_cast<const unsigned char*>(newEntry.searchableURL.c_str()),
                               newEntry.searchableURL.length(), encryptedSearchableURL);

    // Update the DatabaseObject with the encrypted data
    databaseObject.addEntry(PasswordEntry(
        reinterpret_cast<char*>(encryptedPassword),
        reinterpret_cast<char*>(encryptedName),
        reinterpret_cast<char*>(encryptedUrl),
        reinterpret_cast<char*>(encryptedUsername),
        reinterpret_cast<char*>(encryptedNotes)
        // reinterpret_cast<char*>(encryptedSearchableURL)
        ));
  } catch(const std::exception& e) {
    // Handle encryption or database update errors here
    fprintf(stderr, "Error: %s\n", e.what());
    return; // Do not proceed if encryption fails
  }

  // Start a thread to update the database
  // DatabaseUpdateThread* updateThread = new DatabaseUpdateThread;
  // updateThread->setDatabaseObject(&databaseObject);

  // Connect the thread's finished signal to a slot for cleanup
  // connect(updateThread, &QThread::finished, this, &EntryViewer::onDatabaseUpdateFinished);

  // Start the thread
  // updateThread->start();

  // Close the current window
  close();
}

void EntryViewer::onDatabaseUpdateFinished() { update(); }

void EntryViewer::on_Close_clicked() { close(); }

void EntryViewer::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->database = database;
};
