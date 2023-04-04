/**
* BrushProperties.cpp made by Najmingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
* This cpp file uses BrushProperties.h header file and implements all its methods.
*/
#include "brushproperties.h"
#include "ui_brushproperties.h"
#include <QColorDialog>
#include <QColor>
#include "tool.h"

/**
 * @brief BrushProperties::BrushProperties Constructor for BrushProperites. Sets the color of the tool buttons and displays the associated icons.
 * @param parent widget that is used to help handle memory and resources.
 */
BrushProperties::BrushProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrushProperties)
{
    ui->setupUi(this);
    ui->brushButton->setStyleSheet(QString("background-color: grey"));
    ui->colorPaletteButton->setStyleSheet(QString("background-color: black"));

    ui->brushButton->setIcon(QIcon(":/icons/brush_icon.png"));
    ui->brushButton->setIconSize(QSize(90, 90));

    ui->airBrushButton->setIcon(QIcon(":/icons/airbrush_icon.png"));
    ui->airBrushButton->setIconSize(QSize(90, 90));

    ui->fillButton->setIcon(QIcon(":/icons/filltool_icon.png"));
    ui->fillButton->setIconSize(QSize(90, 90));

    ui->eraseButton->setIcon(QIcon(":/icons/erase_icon.png"));
    ui->eraseButton->setIconSize(QSize(90, 90));


    connect(ui->brushButton, &QPushButton::clicked, this, &::BrushProperties::onBrushButtonClicked);
    connect(ui->airBrushButton, &QPushButton::clicked, this, &::BrushProperties::onAirBrushButtonClicked);
    connect(ui->fillButton, &QPushButton::clicked, this, &::BrushProperties::onFillButtonClicked);
    connect(ui->eraseButton, &QPushButton::clicked, this, &::BrushProperties::onEraseButtonClicked);
    connect(ui->colorPaletteButton, &QPushButton::clicked, this, &::BrushProperties::onColorPaletteButtonClicked);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &::BrushProperties::onBrushSizeChanged);
}

/**
 * @brief BrushProperties::~BrushProperties destructor for brushproperties
 */
BrushProperties::~BrushProperties()
{
    delete ui;
}

/**
 * @brief BrushProperties::onBrushSizeChanged Called when the brush size is changed by the user. Changes the brush size.
 */
void BrushProperties::onBrushSizeChanged(){
    tool->setBrushSize(ui->spinBox->value());
}


/**
 * @brief BrushProperties::setTool sets the tool to the highlighted tool button.
 * @param tool this is the tool to be set.
 */
void BrushProperties::setTool(Tool* tool) {
    this->tool = tool;
}


/**
 * @brief BrushProperties::onColorPaletteButtonClicked Displays a window where the user can select a color. Sets that color as the brush color.
 */
void BrushProperties::onColorPaletteButtonClicked()
{
    QColor brushColor = QColorDialog::getColor(currentColor,this,"Choose a Color");
    currentColor = brushColor;
    //setColor(brushColor);
       QString buttonColorString = QString("background-color: %1").arg(brushColor.name());
       ui->colorPaletteButton->setStyleSheet(buttonColorString);
    tool->setColor(currentColor);

}

/**
 * @brief BrushProperties::onBrushButtonClicked Sends signal to alert the cursor to change to a brush icon, highlights the tool's button,
 * and sets the current tool to a brush.
 */
void BrushProperties::onBrushButtonClicked() {

    emit showBrushIcon();
    ui->brushButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(BRUSH);
}

/**
 * @brief BrushProperties::onAirBrushButtonClicked Sends signal to alert the cursor to change to a airbrush icon, highlights the tool's button,
 * and sets the current tool to a air brush.
 */
void BrushProperties::onAirBrushButtonClicked() {
    emit showAirBrushIcon();
    ui->airBrushButton->setStyleSheet(QString("background-color: grey"));
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(AIRBRUSH);
}

/**
 * @brief BrushProperties::onFillButtonClicked Sends signal to alert the cursor to change to a fill icon, highlights the tool's button,
 * and sets the current tool to a fill brush.
 */
void BrushProperties::onFillButtonClicked() {
    emit showFillIcon();
    ui->fillButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    tool->setSelectedToolType(FILL);
}

/**
 * @brief BrushProperties::onEraseButtonClicked Sends signal to alert the cursor to change to a eraser icon, highlights the tool's button,
 * and sets the current tool to a eraser.
 */
void BrushProperties::onEraseButtonClicked() {
    emit showEraseIcon();
    ui->eraseButton->setStyleSheet(QString("background-color: grey"));
    ui->airBrushButton->setStyleSheet("");
    ui->brushButton->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    tool->setSelectedToolType(ERASER);
}
