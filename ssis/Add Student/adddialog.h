#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(MainWindow *parent = nullptr);
    ~addDialog();

    bool isValidCourse(const QString &course, QString &courseCode);
    void saveCsv(const QString &filename, const QString &name, const QString &idnum, const QString &gender, const QString &year, const QString &course);

private slots:
    void on_doneBtn_clicked();

private:
    Ui::addDialog *ui;
    MainWindow *mainwindow;
};

#endif // ADDDIALOG_H
