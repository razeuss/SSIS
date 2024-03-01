#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class addcourse;
}

class addcourse : public QDialog
{
    Q_OBJECT

public:
    explicit addcourse(MainWindow *parent = nullptr);
    ~addcourse();

    void savetocsv(const QString &file, const QString &code, const QString &bs, const QString &course );

private slots:
    void on_done_clicked();

private:
    Ui::addcourse *ui;
    MainWindow *mainwindow;
};

#endif // ADDCOURSE_H

