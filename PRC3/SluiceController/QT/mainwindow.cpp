#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluicetcphandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SluiceTCPHandler* x = new SluiceTCPHandler(0, this);
    x->SetDoor(DoorLeft, DoorStateOpen);
    delete x;
}

MainWindow::~MainWindow()
{
    delete ui;
}
