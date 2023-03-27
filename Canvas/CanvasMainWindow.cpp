#include "CanvasMainWindow.h"
#include "ui_CanvasMainWindow.h"
#include "mycanvas.h"

CanvasMainWindow::CanvasMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CanvasMainWindow)
{
    ui->setupUi(this);
    MyCanvas *canvas = new MyCanvas(this);
    setCentralWidget(canvas);
}

CanvasMainWindow::~CanvasMainWindow()
{
    delete ui;
}

