
#include "brushproperties.h"
#include "ui_brushproperties.h"
#include <QColorDialog>
#include <QColor>
#include "tool.h"


BrushProperties::BrushProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrushProperties)
{
    ui->setupUi(this);
    ui->brushButton->setStyleSheet(QString("background-color: grey"));
    ui->colorPaletteButton->setStyleSheet(QString("background-color: black"));
    connect(ui->brushButton, &QPushButton::clicked, this, &::BrushProperties::onBrushButtonClicked);
    connect(ui->airBrushButton, &QPushButton::clicked, this, &::BrushProperties::onAirBrushButtonClicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &::BrushProperties::onFillButtonClicked);
    connect(ui->eraseButton, &QPushButton::clicked, this, &::BrushProperties::onEraseButtonClicked);
    connect(ui->colorPaletteButton, &QPushButton::clicked, this, &::BrushProperties::onColorPaletteButtonClicked);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &::BrushProperties::onBrushSizeChanged);
}

BrushProperties::~BrushProperties()
{
    delete ui;
}


void BrushProperties::onBrushSizeChanged(){
    tool->setBrushSize(ui->spinBox->value());
}
void BrushProperties::setTool(Tool* tool) {
    this->tool = tool;
}

void BrushProperties::onColorPaletteButtonClicked()
{
    QColor brushColor = QColorDialog::getColor(currentColor,this,"Choose a Color");
    currentColor = brushColor;
    //setColor(brushColor);
       QString buttonColorString = QString("background-color: %1").arg(brushColor.name());
       ui->colorPaletteButton->setStyleSheet(buttonColorString);
    tool->setColor(currentColor);

}

void BrushProperties::onBrushButtonClicked() {

    emit showBrushIcon();


    ui->brushButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(BRUSH);
}

void BrushProperties::onAirBrushButtonClicked() {
    emit showAirBrushIcon();

    ui->airBrushButton->setStyleSheet(QString("background-color: grey"));
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(AIRBRUSH);
}

void BrushProperties::onFillButtonClicked() {
    emit showFillIcon();


    ui->fillButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(FILL);
}

void BrushProperties::onEraseButtonClicked() {
    emit showEraseIcon();



    ui->eraseButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    tool->setSelectedToolType(ERASER);
}
