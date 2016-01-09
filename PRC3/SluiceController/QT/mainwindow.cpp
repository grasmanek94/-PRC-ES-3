#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluis.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::PushButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PushButtonClicked()
{
    Sluis sluis(0);
    sluis.VerplaatsBoot();
}
