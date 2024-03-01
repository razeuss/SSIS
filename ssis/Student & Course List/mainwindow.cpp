#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addDialog.h"
#include "infodialog.h"
#include "addcourse.h"
#include "deletecourse.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QStandardItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString studlist = "C:/Users/jradl/Downloads/Students.csv";
    ui->toolButton->hide();
    csvread(studlist);
    tool_options();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::csvread(const QString &filename)
{
        QStandardItemModel *model = new QStandardItemModel(this);


        QFile file(filename);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            delete model;
            return;
        }

        QTextStream in(&file);
        int row = 0;

        if (filename == "C:/Users/jradl/Downloads/Students.csv")
        {
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList rline = line.split(',');
                for (int i = 0; i < rline.size(); ++i)
                {
                    QString value = rline.at(i);
                    QStandardItem *item = new QStandardItem(value);
                    model->setItem(row, i, item);
                }


                QString idNumber = rline.at(1);
                QString coursecode = rline.at(4);
                studentmap.insert(idNumber, rline);
                course.insert(coursecode, rline);

                row++;
            }

            file.close();

            ui->tableView->setModel(model);

            int columnCount = model->columnCount();
            int columnWidth = ui->tableView->viewport()->width() / columnCount;

            for (int i = 0; i < columnCount; ++i)
                ui->tableView->setColumnWidth(i, columnWidth + (i < ui->tableView->viewport()->width() % columnCount));
        }else {

            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList rline = line.split(',');

                if (rline.size() == 2) {
                    QString value = rline.at(1);
                    QStandardItem *item = new QStandardItem(value);
                    model->setItem(row, 0, item);

                    QString course = rline.at(0);
                    studentmap.insert(course, rline);

                    row++;
                }
            }

            file.close();

            ui->course_view->setModel(model);

            int tableViewWidth = ui->course_view->width();
            int columnWidth = tableViewWidth;
            ui->course_view->setColumnWidth(0, columnWidth);
            ui->course_view->setColumnWidth(1, columnWidth);
        }

}


void MainWindow::on_addbutton_clicked()
{
        addDialog addform(this);
        addform.setModal(true);
        addform.exec();
}

void MainWindow::updateInfo(const QStringList &updatedInfo)
{
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
        qDebug() << "Updating info with " << updatedInfo;

        if (model) {
            for (int row = 0; row < model->rowCount(); ++row) {
                if (model->index(row, 1).data().toString() == updatedInfo[1]) {
                    for (int col = 0; col < model->columnCount(); ++col) {
                        model->setData(model->index(row, col), updatedInfo[col]);
                    }
                    break;
                }
            }
        }

        QFile file("C:/Users/jradl/Downloads/Students.csv");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int row = 0; row < model->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < model->columnCount(); ++col) {
                    rowData << model->index(row, col).data().toString();
                }
                out << rowData.join(",") << "\n";
            }
            file.close();
        } else {
            qDebug() << "Failed to open file for writing.";
        }

}

void MainWindow::on_searchID_clicked()
{
        QString searchID = ui->idinp->text();
        csvread("C:/Users/jradl/Downloads/Students.csv");

        if (studentmap.contains(searchID))
        {
            QStringList studentInfo = studentmap[searchID];

            infoDialog info(this);
            info.StudInfo(studentInfo);
            info.setModal(true);


            connect(&info, &infoDialog::saveButtonClicked, this, &MainWindow::updateInfo);
            connect(&info, &infoDialog::deleteinfo, this, &MainWindow::deleteStudentFromMap);

            info.exec();
        }
        else
        {
            QMessageBox::warning(this, "Student Not Found", "No student found with the entered ID number.");
        }
}

void MainWindow::deleteStudentFromMap(const QString &idNumber)
{
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
        if (!model) {
            qDebug() << "Model is null. Cannot delete student.";
            return;
        }


        studentmap.remove(idNumber);
        course.remove(idNumber);

        for (int row = model->rowCount() - 1; row >= 0; --row) {
            if (model->index(row, 1).data().toString() == idNumber || model->index(row, 4).data().toString() == idNumber) {
                model->removeRow(row);
            }
        }


        QFile file("C:/Users/jradl/Downloads/Students.csv");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int row = 0; row < model->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < model->columnCount(); ++col) {
                    rowData << model->index(row, col).data().toString();
                }
                out << rowData.join(",") << "\n";
            }
            file.close();
        } else {
            qDebug() << "Failed to open file for writing.";
        }
}


void MainWindow::transition()
{
        ui->label_2->setGeometry(521,121,693,24);
        ui->name->setGeometry(590,120,41,21);
        ui->id->setGeometry(710,120,81,21);
        ui->yr->setGeometry(850,120,81,21);
        ui->gender->setGeometry(990,120,61,21);
        ui->tableView->setGeometry(520,120,711,461);
        ui->degree->setGeometry(1110,120,91,21);

        csvread("C:/Users/jradl/Downloads/Students.csv");
}

void MainWindow::on_viewprog_clicked()
{
        QString file = "C:/Users/jradl/OneDrive/Documents/QT creator projects/Courses.csv";
        csvread(file);
        transition();
        ui->toolButton->show();
}

void MainWindow::tool_options()
{
        QMenu *menu = new QMenu(this);
        menu->addAction("Collapse list");
        menu->addAction("Add program");
        menu->addAction("Delete program");

        ui->toolButton->setMenu(menu);
        ui->toolButton->setPopupMode(QToolButton::InstantPopup);
        ui->toolButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");

}


void MainWindow::on_toolButton_triggered(QAction *action)
{

        if (action->text() == "Collapse list") {

            ui->toolButton->hide();
            ui->label_2->setGeometry(241,121,973,24);
            ui->name->setGeometry(340,120,41,21);
            ui->id->setGeometry(520,120,81,21);
            ui->yr->setGeometry(720,120,81,21);
            ui->gender->setGeometry(920,120,61,21);
            ui->tableView->setGeometry(240,120,991,461);
            ui->degree->setGeometry(1090,120,91,21);

            csvread("C:/Users/jradl/Downloads/Students.csv");

        } else if (action->text() == "Add program") {

            addcourse add(this);
            add.setModal(true);
            add.exec();

        } else {

            deleteCourse del(this);
            del.setModal(true);

            connect(&del, &deleteCourse::deleteinfo, this, &MainWindow::deleteStudentFromMap);

            del.exec();
        }
}


