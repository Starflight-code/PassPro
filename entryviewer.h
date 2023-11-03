#ifndef ENTRYVIEWER_H
#define ENTRYVIEWER_H

#include <QMainWindow>

namespace Ui {
    class EntryViewer;
}

class EntryViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit EntryViewer(QWidget* parent = nullptr);
    ~EntryViewer();

private:
    Ui::EntryViewer* ui;
};

#endif // ENTRYVIEWER_H
