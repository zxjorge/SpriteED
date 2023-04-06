/**
 * spritecanvas.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * Model for tools and drawing on images
 * Reviewed by: Najman Husaini
 */
#include <queue>
#include <vector>
#include "tool.h"
#include <algorithm>
#include <QRandomGenerator>
#include <cmath>
#include <QPainter>
#include <QSet>
using std::queue, std::vector;

/// @brief Constructor for the Tool class, sets the default tool.
Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH),
    airBrushDensity(0.05)
{
}

/// @brief Sets the color of the selected tool.
/// @param color The color to be set to the tool.
void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

/// @brief Sets the size of the brush.
/// @param size The size to be set to the tool.
void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

/// @brief Sets the tool type,
/// @param type The type that the tool will be set to.
void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}

/// @brief Used for the fill tool, helps in determining whether or not a point will be filled.
/// @param visited A QSet of QPoints that have been checked for fill eligibility.
/// @param point The point that is being checked for fill eligibility.
/// @param image The QImage representing what has been drawn on the current frame.
/// @param originalColor The color that the fill tool changing.
/// @return True if the point has not been checked and if the color is the original,
/// false otherwise.
bool isValid(QSet<QPoint>& visited, QPoint &point, QImage& image, QColor originalColor) {
    QColor currentColor = image.pixelColor(point);
    return !visited.contains(point) && currentColor == originalColor;
}

/// @brief Used for the fill tool and helps in determine what points on the image need to be filled.
/// @param image The current image that the fill tool is used on.
/// @param point The point where the fill tool was originally applied.
void Tool::fillImageAtPosition(QImage& image, QPoint point){
    QColor fillColor = brushPen.color();
    QColor originalColor = image.pixelColor(point);

    //Queue of points to be filled.
    queue<QPoint> fillQueue = queue<QPoint>();

    //Queue of visited points.
    QSet<QPoint> visited;

    fillQueue.push(point);
    visited.insert(point);

    while (!fillQueue.empty()) {
        QPoint currentPoint = fillQueue.front();
        fillQueue.pop();

        image.setPixelColor(currentPoint, fillColor);
        QPoint tmpPoint = currentPoint;
        tmpPoint.rx() -= 1;

        // The following if statements ensure the point is within the canvas boundary.
        // They also determine whether a point will be filled or not and update the queues accordingly.
        if (tmpPoint.x() >= 0 && isValid(visited, tmpPoint, image, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.insert(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.rx() += 1;
        if (tmpPoint.x() < image.width() && isValid(visited, tmpPoint, image, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.insert(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() += 1;
        if (tmpPoint.y() < image.height() && isValid(visited, tmpPoint, image, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.insert(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() -= 1;
        if (tmpPoint.y() >= 0 && isValid(visited, tmpPoint, image, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.insert(tmpPoint);
        }
    }
}

/// @brief Gets the selected tool type.
/// @return The selected tool type.
ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

/// @brief Used to set the drawing specifications for the airbrush texture.
/// @return The texture that the airbrush uses for drawing.
QImage Tool::getAirBrushTexture() {
    QColor color = brushPen.color();
    QImage texture = QImage(brushPen.width(), brushPen.width(), QImage::Format_ARGB32_Premultiplied);
    texture.fill(QColor(0, 0, 0, 0));
    int pixelCount;
    float radius = brushPen.widthF() / 2;
    QRandomGenerator* rng = QRandomGenerator::global();
    if (brushPen.width() == 1) {
        pixelCount = std::round(rng->bounded(1.0));
    } else {
        pixelCount = std::ceil(M_PI * radius * radius * airBrushDensity);
    }

    // Math for the color variation and determining random points to be filled within the brush size.
    for (int i = 0; i < pixelCount; i++) {
        float angle = rng->bounded(2 * M_PI);
        float distance = rng->bounded(radius);
        int x = radius + distance * sin(angle);
        int y = radius + distance * cos(angle);
        color.setAlphaF(rng->bounded(0.7));
        texture.setPixelColor(x, y, color);
    }

    return texture;
}

/// @brief Fills a pixel on the image with the selected color and associated brush specifications.
/// @param image The current image that is being drawn on.
/// @param point The point that has been modified.
void Tool::drawPointOnImage(QImage& image, QPoint point) {
    QPen pen;
    QPainter painter(&image);

    // The following if statements determine the logic to be used depending on the selected tool.
    if(selectedToolType == ERASER){
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        pen = brushPen;
        pen.setColor(QColor(0, 0, 0, 0));
    } else if(selectedToolType == FILL) {
        fillImageAtPosition(image, point);
        return;
    } else if(selectedToolType == AIRBRUSH) {
        QImage texture = getAirBrushTexture();
        painter.drawImage(QPoint(point.x() - texture.width() / 2, point.y() - texture.width() / 2), texture);
        return;
    } else {
        pen = brushPen;
    }
    painter.setPen(pen);
    painter.drawPoint(point);
}

/// @brief Used for drawing when the mouse is clicked and dragged across the image
/// @param image The current image that is being drawn on.
/// @param from The point where the mouse was clicked.
/// @param to The point where the mouse was released.
void Tool::drawLineOnImage(QImage& image, QPoint from, QPoint to) {
    QPen pen;
    QPainter painter(&image);

    // The following if statements determine the logic to be used depending on the selected tool.
    if(selectedToolType == ERASER){
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        pen = brushPen;
        pen.setColor(QColor(0, 0, 0, 0));
    } else if(selectedToolType == FILL) {
        // Do nothing
        return;
    } else if(selectedToolType == AIRBRUSH) {
        QPoint travel = to - from;
        int travelDistance = travel.manhattanLength();
        if (travelDistance == 0) {
            return;
        }
        QPointF step = travel.toPointF() / travelDistance;

        for (int i = 0; i < travelDistance; i++) {
            QPoint point = (from + step * i).toPoint();
            QImage texture = getAirBrushTexture();
            painter.drawImage(QPoint(point.x() - texture.width() / 2, point.y() - texture.width() / 2), texture);
        }

        return;
    } else {
        pen = brushPen;
    }
    painter.setPen(pen);
    painter.drawLine(from, to);
}
