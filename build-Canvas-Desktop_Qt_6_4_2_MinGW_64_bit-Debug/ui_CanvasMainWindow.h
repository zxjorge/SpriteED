/********************************************************************************
** Form generated from reading UI file 'CanvasMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVASMAINWINDOW_H
#define UI_CANVASMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mycanvas.h"

QT_BEGIN_NAMESPACE

class Ui_CanvasMainWindow
{
public:
    QWidget *centralwidget;
    MyCanvas *widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CanvasMainWindow)
    {
        if (CanvasMainWindow->objectName().isEmpty())
            CanvasMainWindow->setObjectName("CanvasMainWindow");
        CanvasMainWindow->resize(800, 600);
        centralwidget = new QWidget(CanvasMainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new MyCanvas(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 10, 491, 341));
        CanvasMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CanvasMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        CanvasMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CanvasMainWindow);
        statusbar->setObjectName("statusbar");
        CanvasMainWindow->setStatusBar(statusbar);

        retranslateUi(CanvasMainWindow);

        QMetaObject::connectSlotsByName(CanvasMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CanvasMainWindow)
    {
        CanvasMainWindow->setWindowTitle(QCoreApplication::translate("CanvasMainWindow", "CanvasMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CanvasMainWindow: public Ui_CanvasMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVASMAINWINDOW_H
