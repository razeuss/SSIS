#include "infodialog.h"
#include "ui_infodialog.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QFile>

infoDialog::infoDialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog),
    mainwindow(parent)
{
    ui->setupUi(this);
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_editbtn_clicked()
{
    enabler();
    ui->savebtn->setFixedSize(91,31);
}

void infoDialog::enabler()
{
    ui->name->setEnabled(true);
    ui->course->setEnabled(true);
    ui->genderBox->setEnabled(true);
    ui->yrlvlbox->setEnabled(true);

    ui->editbtn->hide();
}

void infoDialog::StudInfo(const QStringList &studentInfo)
{
    ui->name->setText(studentInfo[0].toUpper());
    ui->idnum->setText(studentInfo[1]);
    ui->yrlvlbox->setCurrentText(studentInfo[2].toUpper());
    ui->genderBox->setCurrentText(studentInfo[3].toUpper());
    ui->course->setText(studentInfo[4]);
}

void infoDialog::on_savebtn_clicked()
{
    QString name = ui->name->text();
    QString idnum = ui->idnum->text();
    QString gender = ui->genderBox->currentText();
    QString year = ui->yrlvlbox->currentText();
    QString course = ui->course->text();

    QFile file("C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing: ";
        return;
    }


    QTextStream in(&file);
    bool exists = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2 && parts[0].trimmed().compare(course, Qt::CaseInsensitive) == 0) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        QMessageBox::warning(this, "PROGRAM NOT FOUND", "Academic program does not exist.");
        return;
    } else {
        QMessageBox::information(this, "Operation Successful", "The operation was completed successfully.");
        QStringList updatedInfo;
        updatedInfo << name << idnum << year << gender << course;

        emit saveButtonClicked(updatedInfo);

        close();
    }
}


void infoDialog::on_deletebutton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"CONFIRMATION","Are you sure?",QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes)
    {

        emit deleteinfo(ui->idnum->text());
        close();

    } else {

    }

}
