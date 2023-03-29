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
    void on_colorPaletteButton_clicked();
    void on_brushButton_clicked();
    void on_airBrushButton_clicked();
    void on_fillButton_clicked();
    void on_eraseButton_clicked();

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
