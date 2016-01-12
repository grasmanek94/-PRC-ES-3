#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sluislogic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Schutten();
    void Vrijgeven_In();
    void Vrijgeven_Uit();
    void Alarm();
    void Herstel();

private:
    Ui::MainWindow *ui;
    SluisLogic *sluis;
};

#endif // MAINWINDOW_H
