
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
    QColor brushColor = QColorDialog::getColor(currentColor,this,"Choose a Color");
    currentColor = brushColor;
       QString buttonColorString = QString("background-color: %1").arg(brushColor.name());
       ui->colorPaletteButton->setStyleSheet(buttonColorString);


}

