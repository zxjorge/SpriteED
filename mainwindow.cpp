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
            ui->sprite_canvas,
            &SpriteCanvas::showAirBrushIcon);

    connect(ui->brush_properties,
            &BrushProperties::showFillIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showFillIcon);

    connect(ui->brush_properties,
            &BrushProperties::showEraseIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showEraseIcon);

    connect(ui->brush_properties,
            &BrushProperties::showBrushIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showBrushIcon);

}


MainWindow::~MainWindow()
{
    delete ui;
}

