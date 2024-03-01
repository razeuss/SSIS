#include "deletecourse.h"
#include "ui_deletecourse.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QFile>

deleteCourse::deleteCourse(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::deleteCourse),
    mainwindow(parent)
{
    ui->setupUi(this);
    showcourse();
}

deleteCourse::~deleteCourse()
{
    delete ui;
}

void deleteCourse::showcourse()
{
    QString filepath = "C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv";
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filepath;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            QString courseName = parts[1].trimmed(); // Trimmed to remove leading/trailing spaces
            qDebug() << "Found course:" << courseName;
            ui->comboBox->addItem(courseName);
        }
    }

    file.close();
}

void deleteCourse::deleter(const QString &coursename, QString &code)
{
    QString filePath = "C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv";

    QFile inputFile(filePath);
    if (!inputFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading";
        return;
    }

    QTextStream in(&inputFile);
    QStringList lines;
    bool found = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (!line.contains(coursename)) {
            lines << line;
        } else {
            if (parts.size() >= 1) {
                code = parts[0];
                found = true;


            }
        }
    }

    inputFile.resize(0);

    if (found) {
        QTextStream out(&inputFile);
        out << lines.join("\n");
    }

    inputFile.close();
}

void deleteCourse::on_deletebutton_clicked()
{
    QString course = ui->comboBox->currentText();

    QString code;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "CONFIRMATION", "ARE YOU SURE?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        deleter(course, code);
        emit deleteinfo(code);
        mainwindow->csvread("C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv");

        close();

    }
}
