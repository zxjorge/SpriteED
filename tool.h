#ifndef TOOL_H
#define TOOL_H
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QSet>

enum ToolType{
    BRUSH,
    FILL,
    AIRBRUSH,
    ERASER
};

class Tool
{
public:
    Tool();

    void setColor(QColor color);
    void setBrushSize(int size);
    void setSelectedToolType(ToolType type);

    void drawPointOnImage(QImage& image, QPoint point);
    void drawLineOnImage(QImage& image, QPoint from, QPoint to);

    ToolType getSelectedToolType();

private:
    QPen brushPen;
    ToolType selectedToolType;
    float airBrushDensity;

    QImage getAirBrushTexture();

    void fillImageAtPosition(QImage& image, QPoint point);
};

#endif // TOOL_H
