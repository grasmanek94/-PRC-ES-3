#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluislogic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    sluis[0] = new SluisLogic(0, this);
    sluis[1] = new SluisLogic(1, this);
    sluis[2] = new SluisLogic(3, this);//TODO new SluisLogicOneSecondDoor(3, this);

    ui->setupUi(this);
    connect(ui->b_Schutten, &QPushButton::clicked, this, &MainWindow::Schutten);
    connect(ui->b_Vrijgeven, &QPushButton::clicked, this, &MainWindow::Vrijgeven);
    connect(ui->b_Alarm, &QPushButton::clicked, this, &MainWindow::Alarm);
    connect(ui->b_Herstel, &QPushButton::clicked, this, &MainWindow::Herstel);
 }

SluisLogic* MainWindow::GetSelectedSluis()
{
    if(ui->rb_1->isChecked())
    {
        return sluis[0];
    }
    else if(ui->rb_2->isChecked())
    {
        return sluis[1];
    }
    else if(ui->rb_3->isChecked())
    {
        return sluis[2];
    }
    //should not happen
    return NULL;
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < 3; ++i)
    {
        delete sluis[i];
        sluis[i] = NULL;
    }
    delete ui;
    ui = NULL;
}

void MainWindow::Schutten()
{
    GetSelectedSluis()->Schutten();
}

void MainWindow::Vrijgeven()
{
    GetSelectedSluis()->Vrijgeven();
}

void MainWindow::Alarm()
{
    GetSelectedSluis()->Alarm();
}

void MainWindow::Herstel()
{
    GetSelectedSluis()->Herstel();
}
