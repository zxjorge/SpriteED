#ifndef BRUSHPROPERTIES_H
#define BRUSHPROPERTIES_H

#include <QWidget>


namespace Ui {
class BrushProperties;
}

class BrushProperties : public QWidget
{
    Q_OBJECT

public:
    explicit BrushProperties(QWidget *parent = nullptr);
    ~BrushProperties();

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
};

#endif // BRUSHPROPERTIES_H
