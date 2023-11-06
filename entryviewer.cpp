#include "entryviewer.h"
#include "ui_entryviewer.h"

EntryViewer::EntryViewer(QWidget* parent) : QMainWindow(parent), ui(new Ui::EntryViewer) {
  ui->setupUi(this);
}

EntryViewer::~EntryViewer() {
  delete ui;
}
