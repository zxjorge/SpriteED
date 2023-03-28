
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
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose a Color");
}

