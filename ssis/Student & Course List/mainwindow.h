#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void csvread(const QString &filename);
    void updateInfo(const QStringList &updatedInfo);
    void tool_options();
    void transition();

private slots:
    void on_addbutton_clicked();
    void on_searchID_clicked();
    void on_toolButton_triggered(QAction *arg1);
    void on_viewprog_clicked();

public slots:
    void deleteStudentFromMap(const QString &idNumber);

private:
    Ui::MainWindow *ui;

    QSet<QString> coursesSet;
    QMap<QString, QStringList> studentmap;
    QMap<QString, QStringList> course;

};
#endif // MAINWINDOW_H
