#include "entryviewer.h"
#include "ui_entryviewer.h"

#include "Data Storage/DatabaseManager.h"
#include "Data Storage/DatabaseObject.h"
#include "Data Structures/PasswordEntry.h"

#include <QThread>

DatabaseManager databaseManager;

class DatabaseUpdateThread : public QThread {
public:
  void run() override { updateDatabase(); }
};

EntryViewer::EntryViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::EntryViewer) {
  ui->setupUi(this);

  connect(ui->pushButton_2, &QPushButton::clicked, this,
          &EntryViewer::on_pushButton_2_clicked);
  connect(ui->Password, &QLineEdit::editingFinished, this,
          &EntryViewer::on_Password_editingFinished);
}

EntryViewer::~EntryViewer() { delete ui; }

DatabaseObject databaseObject;
void EntryViewer::on_pushButton_2_clicked() {

  PasswordEntry newEntry(
      ui->Password->text().toStdString(), ui->Name->text().toStdString(),
      ui->URL->text().toStdString(), ui->Username->text().toStdString(),
      ui->Notes->text().toStdString());
  databaseObject.addEntry(newEntry);

  DatabaseUpdateThread *updateThread = new DatabaseUpdateThread;
  connect(updateThread, &QThread::finished, this,
          &EntryViewer::onDatabaseUpdateFinished);
  updateThread->start();

  databaseManager.writeDB();
  main::updateDatabase();
  update();
}

void EntryViewer::onDatabaseUpdateFinished() { update(); }

void EntryViewer::on_Close_clicked() { EntryViewer::~EntryViewer(); }
