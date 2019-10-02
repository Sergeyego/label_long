#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include "lblengine.h"
#include <QMainWindow>
#include <QCalendarWidget>
#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *modelMar;
    QSqlQueryModel *modelDiam;
    //QSqlQueryModel *modelNam;
    QSqlQueryModel *modelGost;
    void setQueryModel(QString query, QSqlQueryModel *model);
private slots:
    void genLabel();
    void updModels();
    void selGost();
};

#endif // MAINWINDOW_H
