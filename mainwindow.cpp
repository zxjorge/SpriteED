#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spritecanvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SpriteCanvas *canvas = new SpriteCanvas(this);
    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

