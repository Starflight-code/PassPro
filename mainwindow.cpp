#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  bool inClassDemo = true;

  if (inClassDemo) {
    ui->tableView->hide();
  } else {
  ui->columnView->hide();
  ui->columnView_2->hide();
  ui->columnView_3->hide();
  ui->columnView_4->hide();
  }

  QStandardItemModel tableContent(2, 2);
  for (int row = 0; row < tableContent.rowCount(); ++row) {
    for (int column = 0; column < tableContent.columnCount(); ++column) {
      QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
      tableContent.setItem(row, column, item);
    }
  }
  ui->tableView->setModel(&tableContent);
  //ui->tableView->update();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  entry.show();
}

