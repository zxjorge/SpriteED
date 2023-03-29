
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
    connect(ui->brushButton, &QPushButton::clicked, this, &BrushProperties::on_brushButton_clicked);
    connect(ui->airBrushButton, &QPushButton::clicked, this, &BrushProperties::on_airBrushButton_clicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &BrushProperties::on_fillButton_clicked);
    connect(ui->eraseButton, &QPushButton::clicked, this, &BrushProperties::on_eraseButton_clicked);

}

BrushProperties::~BrushProperties()
{
    delete ui;
}

void BrushProperties::setTool(Tool* tool) {
    this->tool = tool;
}

void BrushProperties::on_colorPaletteButton_clicked()
{
    QColor brushColor = QColorDialog::getColor(currentColor,this,"Choose a Color");
    currentColor = brushColor;
    //setColor(brushColor);
       QString buttonColorString = QString("background-color: %1").arg(brushColor.name());
       ui->colorPaletteButton->setStyleSheet(buttonColorString);
    tool->setColor(currentColor);

}

void BrushProperties::on_brushButton_clicked() {

    emit showBrushIcon();

    //QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));

    ui->brushButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
}

void BrushProperties::on_airBrushButton_clicked() {
    emit showAirBrushIcon();

    ui->airBrushButton->setStyleSheet(QString("background-color: grey"));
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
}

void BrushProperties::on_fillButton_clicked() {
    emit showFillIcon();


    ui->fillButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
}

void BrushProperties::on_eraseButton_clicked() {
    emit showEraseIcon();



    ui->eraseButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
}
