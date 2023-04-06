/**
 * main.cpp made by Najmingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * Entry point for the application
 * Singletons are initialized here
 * Reviewed by: Najman Husaini
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tool tool;
    AnimationFrames frames;
    MainWindow w(&tool, &frames);
    w.show();
    w.setWindowTitle("Sprite Editor");
    QIcon icon(":/icons/logo.png");
    w.setWindowIcon(icon);
    return a.exec();
}
