#ifndef TOOL_H
#define TOOL_H
#include <QColor>
#include <QBrush>
#include <QPen>

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

    ToolType getSelectedToolType();
    QPen* getBrushPen();
    QPen getAirBrushPen();
    QPen* getErasePen();
    QColor getFillColor();

private:
    QPen brushPen;
    QPen erasePen;
    ToolType selectedToolType;
};

#endif // TOOL_H
