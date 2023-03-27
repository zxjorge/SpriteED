#include "CanvasMainWindow.h"
#include "MyCanvas.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanvasMainWindow w;
    w.show();
    return a.exec();
