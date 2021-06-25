/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *content;
    QLineEdit *name;
    QPushButton *guardarBoton;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuceROBOT;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        content = new QTextEdit(centralwidget);
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(50, 160, 711, 371));
        name = new QLineEdit(centralwidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(40, 20, 113, 25));
        guardarBoton = new QPushButton(centralwidget);
        guardarBoton->setObjectName(QString::fromUtf8("guardarBoton"));
        guardarBoton->setGeometry(QRect(40, 70, 111, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(450, 70, 221, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuceROBOT = new QMenu(menubar);
        menuceROBOT->setObjectName(QString::fromUtf8("menuceROBOT"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuceROBOT->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        guardarBoton->setText(QCoreApplication::translate("MainWindow", "Guardar Libro", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Partir todos los libros", nullptr));
        menuceROBOT->setTitle(QCoreApplication::translate("MainWindow", "ceROBOT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
