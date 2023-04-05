#include "mainwindow.h"
#include <QApplication>

/*
 * NajMingle: 
 * CS3505
 * A7: Sprite Editor
 * 
 */

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
