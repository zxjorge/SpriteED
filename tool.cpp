#include <queue>
#include <vector>
#include "tool.h"
#include <algorithm>
#include <QRandomGenerator>
#include <cmath>
#include <QPainter>
#include <QSet>
using std::queue;
using std::vector;

/// @brief 
Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH),
    airBrushDensity(0.05)
{

}

/// @brief 
/// @param color 
void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

/// @brief 
/// @param size 
void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

/// @brief 
/// @param type 
void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}

/// @brief 
/// @param visited 
/// @param point 
/// @param image 
/// @param originalColor 
/// @return 
bool isValid(QSet<QPoint>& visited, QPoint &point, QImage& image, QColor originalColor) {
    QColor currentColor = image.pixel(point);
    return !visited.contains(point) && currentColor == originalColor;
}

/// @brief 
/// @param image 
/// @param point 
void Tool::fillImageAtPosition(QImage& image, QPoint point){
    QColor fillColor = brushPen.color();
    QColor originalColor = image.pixel(point);
    queue<QPoint> fillQueue = queue<QPoint>();
    QSet<QPoint> visited;


    fillQueue.push(point);
    visited.insert(point);

    while (!fillQueue.empty()) {
        QPoint currentPoint = fillQueue.front();
        fillQueue.pop();

        image.setPixelColor(currentPoint, fillColor);
        QPoint tmpPoint = currentPoint;
        tmpPoint.rx() -= 1;
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

/// @brief 
/// @return 
ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

/// @brief 
/// @return 
QImage Tool::getAirBrushTexture() {
    QColor color = brushPen.color();
    QImage texture = QImage(brushPen.width(), brushPen.width(), QImage::Format_ARGB32_Premultiplied);
    texture.fill(QColor(0, 0, 0, 0));
    float radius = brushPen.widthF() / 2;
    int pixelCount = std::ceil(M_PI * radius * radius * airBrushDensity);
    QRandomGenerator* rng = QRandomGenerator::global();

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

/// @brief 
/// @param image 
/// @param point 
void Tool::drawPointOnImage(QImage& image, QPoint point) {
    QPen pen;
    if(selectedToolType == ERASER){
        pen = brushPen;
        pen.setColor(Qt::white);
    } else if(selectedToolType == FILL) {
        fillImageAtPosition(image, point);
        return;
    } else if(selectedToolType == AIRBRUSH) {
        QPainter painter(&image);
        QImage texture = getAirBrushTexture();
        painter.drawImage(QPoint(point.x() - texture.width() / 2, point.y() - texture.width() / 2), texture);
        return;
    } else {
        pen = brushPen;
    }
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawPoint(point);
}

/// @brief 
/// @param image 
/// @param from 
/// @param to 
void Tool::drawLineOnImage(QImage& image, QPoint from, QPoint to) {
    QPen pen;
    if(selectedToolType == ERASER){
        pen = brushPen;
        pen.setColor(Qt::white);
    } else if(selectedToolType == FILL) {
        // Do nothing
        return;
    } else if(selectedToolType == AIRBRUSH) {
        QPainter painter(&image);
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
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawLine(from, to);
}
