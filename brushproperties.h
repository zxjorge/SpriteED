#ifndef BRUSHPROPERTIES_H
#define BRUSHPROPERTIES_H

#include <QWidget>
#include "tool.h"


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
