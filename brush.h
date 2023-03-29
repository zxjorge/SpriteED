#ifndef BRUSH_H
#define BRUSH_H
#include <QColor>
class Brush
{
public:

    Brush();

    enum BrushType{

    };

    void setColor(QColor color);
    void setBrushSize(int size);
    void setBrushType(BrushType type);

    QColor getColor();
    int getBrushSize();
    BrushType getBrushType();

private:
    int brushSize;
    QColor brushColor;
};

#endif // BRUSH_H
