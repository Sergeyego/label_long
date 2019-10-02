#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);
    QCalendarWidget * pCW = new QCalendarWidget(this);
    pCW->setFirstDayOfWeek( Qt::Monday );
    ui->dateEdit->setCalendarWidget( pCW );

    modelMar=new QSqlQueryModel(this);
    modelDiam=new QSqlQueryModel(this);
    modelGost=new QSqlQueryModel(this);

    updModels();

    ui->boxMarka->setModel(modelMar);
    ui->boxMarka->setModelColumn(1);
    ui->boxDiam->setModel(modelDiam);
    ui->boxDiam->setModelColumn(1); 
    ui->listViewGost->setModel(modelGost);
    selGost();

    connect(ui->cmdPrint,SIGNAL(clicked()),this,SLOT(genLabel()));
    connect(ui->cmdUpd,SIGNAL(clicked(bool)),this,SLOT(updModels()));
    connect(ui->boxMarka,SIGNAL(activated(int)),this,SLOT(selGost()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::genLabel()
{
    QString str;
    str+=tr("Марка - ");
    str+=ui->boxMarka->currentText();
    str+="\n";
    str+=tr("Диаметр, мм - ");
    str+=ui->boxDiam->currentText();
    str+="\n";
    str+=tr("Плавка - ");
    str+=ui->editPlav->text();
    str+="\n";
    str+=tr("Партия - ");
    str+=ui->editPart->text();
    str+="\n";
    str+=tr("Длина, мм - ");
    str+=ui->lineEditL->text();
    str+="\n";
    str+=tr("Масса нетто, кг - ");
    str+=ui->editMas->text();
    str+="\n";
    str+=tr("Дата - ");
    str+=ui->dateEdit->date().toString("dd.MM.yy");
    str+="\n";
    for (int i=0; i<modelGost->rowCount(); i++){
        str+=modelGost->data(modelGost->index(i,0),Qt::EditRole).toString();
        str+="\n";
    }

    LblEngine e;
    e.createLblEd(str,QString());
}

void MainWindow::updModels()
{
    setQueryModel("select id, nam from provol where is_w=1 order by nam",modelMar);
    setQueryModel("select id, sdim from diam order by sdim",modelDiam);
}

void MainWindow::selGost()
{
    QString stquery;
    stquery="select g.nam from gost_new g inner join wire_gost w on g.id=w.id_gost "
            "where w.id_provol="+modelMar->data(ui->boxMarka->model()->index(ui->boxMarka->currentIndex(),0),Qt::EditRole).toString();
    setQueryModel(stquery,modelGost);
}

void MainWindow::setQueryModel(QString query, QSqlQueryModel *model)
{
    model->setQuery(query);
    if (model->lastError().isValid()){
        QMessageBox::critical(this,tr("Ошибка"),model->lastError().text(),QMessageBox::Ok);
    }
}
