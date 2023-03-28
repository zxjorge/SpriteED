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

private:
    Ui::BrushProperties *ui;
};

#endif // BRUSHPROPERTIES_H
