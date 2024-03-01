#ifndef DELETECOURSE_H
#define DELETECOURSE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class deleteCourse;
}

class deleteCourse : public QDialog
{
    Q_OBJECT

public:
    explicit deleteCourse(MainWindow *parent = nullptr);
    ~deleteCourse();

    void deleter(const QString &coursename, QString &code);
    void showcourse();

private slots:
    void on_deletebutton_clicked();

signals:
    void deleteinfo(const QString &idNumber);

private:
    Ui::deleteCourse *ui;
    MainWindow *mainwindow;
};

#endif // DELETECOURSE_H
