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

/**
 * @brief Tool::Tool Constructs a default toolset
 */
Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH),
    airBrushDensity(0.05)
{
}

/**
 * @brief Tool::setColor Sets the color of the selected tool.
 * @param colorThe color to be set to the tool.
 */
void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

/**
 * @brief Tool::setBrushSize Sets the size of the brush.
 * @param size The size to be set to the tool.
 */
void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

/**
 * @brief Tool::setSelectedToolType Sets the tool type
 * @param type The type that the tool will be set to
 */
void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}

/**
 * @brief isValid Used for the fill tool, determinines whether or not a point will be filled.
 * @param visited A QSet of QPoints that have been checked for fill eligibility
 * @param point The point that is being checked for fill eligibility
 * @param image The QImage of the current frame
 * @param originalColor The color that the fill tool will replace
 * @return True iff the point can be filled
 */
bool isValid(QSet<QPoint>& visited, QPoint &point, QImage& image, QColor originalColor) {
    QColor currentColor = image.pixelColor(point);
    return !visited.contains(point) && currentColor == originalColor;
}

/**
 * @brief Tool::fillImageAtPosition Fills the given image at the given position
 * @param image The image to draw on
 * @param point The point to start filling in
 */
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

/**
 * @brief Tool::getSelectedToolType Gets the selected tool type.
 * @return The selected tool type.
 */
ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

/**
 * @brief Tool::getAirBrushTexture Generates the texture to use for drawing with an airbrush
 * @return The texture that the airbrush uses for drawing.
 */
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

/**
 * @brief Tool::drawPointOnImage Draws on a single point using the current tool.
 * @param image The image to draw on
 * @param point The point to draw at
 */
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

/**
 * @brief Tool::drawLineOnImage Draws along a line using the current tool.
 * @param image The image to draw on
 * @param from The starting point of the line
 * @param to The ending point of the line
 */
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
