#include "brushproperties.h"
#include "ui_brushproperties.h"

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
