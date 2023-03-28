
#include "brushproperties.h"
#include "ui_brushproperties.h"
#include <QColorDialog>
#include <QColor>


BrushProperties::BrushProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrushProperties)
{
    ui->setupUi(this);


}

BrushProperties::~BrushProperties()
{
    delete ui;
}



void BrushProperties::on_colorPaletteButton_clicked()
{
    QColor color = QColorDialog::getColor(currentColor,this,"Choose a Color");
    currentColor = color;
    QPalette pal = ui->colorPaletteButton->palette();
    pal.setColor(QPalette::Button, QColor(color));
    ui->colorPaletteButton->setAutoFillBackground(true);
    ui->colorPaletteButton->setPalette(pal);
    ui->colorPaletteButton->update();
}

