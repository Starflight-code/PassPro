#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Cryptography/CryptographyStorage.h"
#include "entryviewer.h"
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QStandardItemModel tableContent;

  private slots:
  void on_pushButton_clicked();

  private:
  Ui::MainWindow* ui;
  EntryViewer entry;
  CryptographyStorage* userCredentials;
};
#endif // MAINWINDOW_H
