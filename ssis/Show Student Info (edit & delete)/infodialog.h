#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class infoDialog;
}

class infoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit infoDialog(MainWindow *parent = nullptr);
    ~infoDialog();

    void enabler();
    void StudInfo(const QStringList &studentInfo);
    void updateInfo(const QStringList& updatedInfo);

signals:
    void saveButtonClicked(const QStringList &updatedInfo);
    void deleteinfo(const QString &idNumber);


private slots:
    void on_editbtn_clicked();

    void on_savebtn_clicked();

    void on_deletebutton_clicked();
public slots:


private:
    Ui::infoDialog *ui;
    QMap<QString, QStringList> studentmap;
    MainWindow *mainwindow;
};

#endif // INFODIALOG_H
