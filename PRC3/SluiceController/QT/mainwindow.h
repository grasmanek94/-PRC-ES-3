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
    void Vrijgeven();
    void Alarm();
    void Herstel();

private:
    SluisLogic* GetSelectedSluis();
    Ui::MainWindow *ui;
    SluisLogic *sluis[3];
};

#endif // MAINWINDOW_H
