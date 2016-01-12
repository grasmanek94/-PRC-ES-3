/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *b_Schutten;
    QPushButton *b_Vrijgeven;
    QPushButton *b_Alarm;
    QPushButton *b_Herstel;
    QRadioButton *rb_1;
    QRadioButton *rb_2;
    QRadioButton *rb_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(257, 124);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        b_Schutten = new QPushButton(centralWidget);
        b_Schutten->setObjectName(QStringLiteral("b_Schutten"));
        b_Schutten->setGeometry(QRect(10, 10, 81, 22));
        b_Vrijgeven = new QPushButton(centralWidget);
        b_Vrijgeven->setObjectName(QStringLiteral("b_Vrijgeven"));
        b_Vrijgeven->setGeometry(QRect(10, 40, 81, 22));
        b_Alarm = new QPushButton(centralWidget);
        b_Alarm->setObjectName(QStringLiteral("b_Alarm"));
        b_Alarm->setGeometry(QRect(110, 10, 81, 22));
        b_Herstel = new QPushButton(centralWidget);
        b_Herstel->setObjectName(QStringLiteral("b_Herstel"));
        b_Herstel->setGeometry(QRect(110, 40, 81, 22));
        rb_1 = new QRadioButton(centralWidget);
        rb_1->setObjectName(QStringLiteral("rb_1"));
        rb_1->setGeometry(QRect(200, 10, 102, 20));
        rb_1->setChecked(true);
        rb_2 = new QRadioButton(centralWidget);
        rb_2->setObjectName(QStringLiteral("rb_2"));
        rb_2->setGeometry(QRect(200, 30, 102, 20));
        rb_3 = new QRadioButton(centralWidget);
        rb_3->setObjectName(QStringLiteral("rb_3"));
        rb_3->setGeometry(QRect(200, 50, 102, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 257, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        b_Schutten->setText(QApplication::translate("MainWindow", "Schutten", 0));
        b_Vrijgeven->setText(QApplication::translate("MainWindow", "Vrijgeven", 0));
        b_Alarm->setText(QApplication::translate("MainWindow", "Alarm", 0));
        b_Herstel->setText(QApplication::translate("MainWindow", "Herstel", 0));
        rb_1->setText(QApplication::translate("MainWindow", "Sluis 1", 0));
        rb_2->setText(QApplication::translate("MainWindow", "Sluis 2", 0));
        rb_3->setText(QApplication::translate("MainWindow", "Sluis 3", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
