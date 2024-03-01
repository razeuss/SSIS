#include "addcourse.h"
#include "ui_addcourse.h"

#include <QFile>
#include <QMessageBox>

addcourse::addcourse(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::addcourse),
    mainwindow(parent)

{
    ui->setupUi(this);
}

addcourse::~addcourse()
{
    delete ui;
}

void addcourse::on_done_clicked()
{
    QString code = ui->coursecode->text();
    QString bs = ui->options->currentText();
    QString course = ui->coursename->text();

    QString path = "C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv";
    savetocsv(path, code, bs, course);

    mainwindow->csvread(path);

}

void addcourse::savetocsv(const QString &filepath, const QString &code, const QString &bs, const QString &course)
{
    QFile file(filepath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing: " << filepath;
        return;
    }

    QTextStream out(&file);

    if (code.isEmpty() || course.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please provide both the course code and course name.");
        file.close();
        return;
    }

    file.seek(file.size());
    out << code << "," << bs + " in " + course << "\n";

    file.close();
    this->close();
}
