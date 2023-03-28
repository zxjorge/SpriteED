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

private:
    Ui::BrushProperties *ui;
};

#endif // BRUSHPROPERTIES_H
