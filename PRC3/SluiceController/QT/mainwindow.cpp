#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluis.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    sluis = new Sluis(0, this);
    ui->setupUi(this);
    connect(ui->b_Schutten, &QPushButton::clicked, this, &MainWindow::Schutten);
    connect(ui->b_Vrijgeven_In, &QPushButton::clicked, this, &MainWindow::Vrijgeven_In);
    connect(ui->b_Vrijgeven_Uit, &QPushButton::clicked, this, &MainWindow::Vrijgeven_Uit);
    connect(ui->b_Alarm, &QPushButton::clicked, this, &MainWindow::Alarm);
    connect(ui->b_Herstel, &QPushButton::clicked, this, &MainWindow::Herstel);
 }

MainWindow::~MainWindow()
{
    delete sluis;
    delete ui;
}

void MainWindow::Schutten()
{
    sluis->Schutten();
}

void MainWindow::Vrijgeven_Uit()
{
    sluis->Vrijgeven_Uit();
}

void MainWindow::Vrijgeven_In()
{
    sluis->Vrijgeven_In();
}

void MainWindow::Alarm()
{

}

void MainWindow::Herstel()
{

}
