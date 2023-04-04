#ifndef BRUSHPROPERTIES_H
#define BRUSHPROPERTIES_H

#include <QWidget>
#include "tool.h"

/**
 * BrushProperties.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * This header file will be used by BrushProperties.cpp and has methods, signals, and slots to handle
 * the users ability to select different tools, showing which tool is currently selected and displaying the current brush color.
 */
namespace Ui {
class BrushProperties;
}

class BrushProperties : public QWidget
{
    Q_OBJECT

public:
    explicit BrushProperties(QWidget *parent = nullptr);
    ~BrushProperties();

    void setTool(Tool* tool);

private slots:
    void onColorPaletteButtonClicked();
    void onBrushButtonClicked();
    void onAirBrushButtonClicked();
    void onFillButtonClicked();
    void onEraseButtonClicked();
    void onBrushSizeChanged();

signals:
    void showFillIcon();
    void showEraseIcon();
    void showAirBrushIcon();
    void showBrushIcon();


private:
    Ui::BrushProperties *ui;
    QColor currentColor = Qt::white;
    Tool* tool;
};

#endif // BRUSHPROPERTIES_H
