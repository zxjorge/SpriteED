/**
 * spritecanvas.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * Model for tools and drawing on images
 * Reviewed by: Najman Husaini
 */
#ifndef TOOL_H
#define TOOL_H
#include <QColor>
#include <QBrush>
#include <QPen>

/// Represents all 4 tool types
enum ToolType{
    BRUSH,
    FILL,
    AIRBRUSH,
    ERASER
};

/**
 * @brief The Tool model
 */
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
