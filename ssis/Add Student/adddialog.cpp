#include "adddialog.h"
#include "ui_adddialog.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>

addDialog::addDialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::addDialog),
    mainwindow(parent)
{
    ui->setupUi(this);
}

addDialog::~addDialog()
{
    delete ui;
}

void addDialog::on_doneBtn_clicked()
{
    QString name = ui->name->text().trimmed().toUpper();
    QString idnum = ui->idnum->text().trimmed().toUpper();
    QString gender = ui->genderBox->currentText().trimmed().toUpper();
    QString year = ui->yrlvlbox->currentText().trimmed().toUpper();
    QString course = ui->course->text().trimmed();
    QString courseCode;

    if (name.isEmpty() || idnum.isEmpty() || course.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields.");
        return;
    }

    if (!isValidCourse(course, courseCode)) {
        QMessageBox::warning(this, "Invalid Course", "The entered course is not valid.");
        return;
    }

    QString filepath = "C:/Users/jradl/Downloads/Students.csv";
    saveCsv(filepath, name, idnum, gender, year, courseCode);

    mainwindow->csvread(filepath);
    this->hide();
}

bool addDialog::isValidCourse(const QString &course, QString &courseCode)
{
    QString courseFilepath = "C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv";
    QFile file(courseFilepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open course file: " << courseFilepath;
        return false;
    }

    QTextStream in(&file);
    bool isValid = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2 && (parts[0].trimmed().compare(course, Qt::CaseInsensitive) == 0 ||
                                  parts[1].trimmed().compare(course, Qt::CaseInsensitive) == 0)) {
            isValid = true;
            courseCode = parts[0].trimmed();
            break;
        }
    }

    file.close();
    return isValid;
}

void addDialog::saveCsv(const QString &filename, const QString &name, const QString &idnum,
                        const QString &gender, const QString &year, const QString &course)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing: " << filename;
        return;
    }

    QTextStream in(&file);
    bool exists = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2 && parts[1].trimmed().compare(idnum, Qt::CaseInsensitive) == 0) {
            exists = true;
            break;
        }
    }

    if (exists) {
        QMessageBox::warning(this, "Duplicate ID Number", "Student with ID number " + idnum + " already exists.");
    } else {
        file.seek(0);

        QTextStream out(&file);
        out << name << "," << idnum << "," << year << "," << gender << "," << course << "\n";
        file.close();
    }
}
