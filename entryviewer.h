#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include <QMainWindow>

namespace Ui {
class EntryViewer;
}

class EntryViewer : public QMainWindow {
  Q_OBJECT

public:
  explicit EntryViewer(QWidget *parent = nullptr);
  ~EntryViewer();
  void onDatabaseUpdateFinished();

private slots:
  void on_Close_clicked();

private slots:
  void on_pushButton_2_clicked();

private:
  Ui::EntryViewer *ui;
};

#endif // ENTRYVIEWER_H
