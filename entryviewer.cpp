#include "entryviewer.h"

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

void EntryViewer::on_pushButton_2_clicked() {

  data->entries.push_back(PasswordEntry(
      ui->Password->text().toStdString(), ui->Name->text().toStdString(),
      ui->URL->text().toStdString(), ui->Username->text().toStdString(),
      ui->Notes->text().toStdString()));

  auto saveTask = [](DatabaseManager* data, CryptographyStorage* credentials) {
    data->writeDB(credentials);
  };

  pool->push_task(saveTask, data, userCredentials);

  /*const unsigned char exampleKey[] = {
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
    //unsigned char encryptedSearchableURL[256];

         // Add the entry to the DatabaseObject
  databaseObject.addEntry(newEntry);

         // Sanitize the DatabaseObject
  //nlohmann::json sanitizedData = databaseManager.sanitizeJSON();

         // Convert the JSON to a string
  //std::string jsonString = sanitizedData.dump();

         // Assuming you have an instance of your Cryptography class named 'crypto'
  //Cryptography crypto;

  // Start the thread
  // updateThread->start();*/

  // Assuming you have a method to update the UI after the database is updated
  onDatabaseUpdateFinished();

  // Clear all fields and close the window
  clearAll();
  hide();
}

void EntryViewer::onDatabaseUpdateFinished() { update(); }

void EntryViewer::on_Close_clicked() {
  clearAll();
  hide();
}

void EntryViewer::tricklePointers(CryptographyStorage* userCredentials, BS::thread_pool* pool, DatabaseManager* database) {
  this->userCredentials = userCredentials;
  this->pool = pool;
  this->data = database;
};

void EntryViewer::clearAll() {
  ui->Password->setText("");
  ui->Name->setText("");
  ui->URL->setText("");
  ui->Username->setText("");
  ui->Notes->setText("");
}
void EntryViewer::setPasswordText(const QString& text)
{
  ui->Password->setText(text);
}

void EntryViewer::setNameText(const QString& text)
{
  ui->Name->setText(text);
}

void EntryViewer::setURLText(const QString& text)
{
  ui->URL->setText(text);
}

void EntryViewer::setUsernameText(const QString& text)
{
  ui->Username->setText(text);
}

void EntryViewer::setNotesText(const QString& text)
{
  ui->Notes->setText(text);
}
