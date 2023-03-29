#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brushproperties.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->brush_properties,
            &BrushProperties::showAirBrushIcon,
            this,
            &MainWindow::showAirBrushIcon);

    connect(ui->brush_properties,
            &BrushProperties::showFillIcon,
            this,
            &MainWindow::showFillIcon);

    connect(ui->brush_properties,
            &BrushProperties::showEraseIcon,
            this,
            &MainWindow::showEraseIcon);

    connect(ui->brush_properties,
            &BrushProperties::showBrushIcon,
            this,
            &MainWindow::showBrushIcon);

}

void showAirBrushIcon(){
    QPixmap brushPixmap(":/icons/airbrush_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);

}
void showFillIcon(){
    QPixmap brushPixmap(":/icons/filltool_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);

}
void showEraseIcon(){
    QPixmap brushPixmap(":/icons/erase_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);

}
void showBrushIcon(){
    QPixmap brushPixmap(":/icons/brush_icon .png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

