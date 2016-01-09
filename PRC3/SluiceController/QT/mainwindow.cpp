#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluicetcphandler.h"
#include "qwst.h"
#include <QWebSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qwst* q = new qwst();
    SluiceTCPHandler* x = new SluiceTCPHandler(0, this);
    x->SetDoor(DoorLeft, DoorStateOpen);
    delete x;
}

MainWindow::~MainWindow()
{
    delete ui;
}
