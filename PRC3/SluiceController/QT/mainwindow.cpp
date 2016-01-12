#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sluislogic.h"

/*#include <QMessageBox>
void qinfo(QString a, QString b)
{
    QMessageBox msgBox;
    msgBox.setText(a);
    msgBox.setInformativeText(b);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}*/

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

void MainWindow::qinfo(QString a, QString b)
{
    ui->txt_info_box->setText(a + "\r\n" + b);
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
    if(GetSelectedSluis()->Schutten())
    {
        qinfo("Informatie", "Schutten gelukt");
    }
    else
    {
        qinfo("Fout", "Schutten niet gelukt, wacht, probeer opnieuw, of probeer eerst Vrijgeven");
    }
}

void MainWindow::Vrijgeven()
{
    if(GetSelectedSluis()->Vrijgeven())
    {
        qinfo("Informatie", "Vrijgeven gelukt");
    }
    else
    {
        qinfo("Fout", "Vrijgeven niet gelukt, probeer opnieuw of probeer Schutten uit");
    }
}

void MainWindow::Alarm()
{
    if(GetSelectedSluis()->Alarm())
    {
        qinfo("Informatie", "Alarm procedure is nu bezig");
    }
    else
    {
        qinfo("Fout", "Niet verbonden");
    }
}

void MainWindow::Herstel()
{
    if(GetSelectedSluis()->Herstel())
    {
        qinfo("Informatie", "Herstel gelukt");
    }
    else
    {
        qinfo("Fout", "Herstel niet gelukt, probeer opnieuw");
    }
}
