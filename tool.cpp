#include <queue>
#include <vector>
#include "tool.h"
#include <algorithm>
#include <QRandomGenerator>
#include <cmath>
#include <QPainter>

using std::queue;
using std::vector;

Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH),
    airBrushDensity(0.05)
{

}

void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}

bool isValid(vector<QPoint>& visited, QPoint point, QColor currentColor, QColor originalColor) {
    return std::find(visited.begin(), visited.end(), point) == visited.end() && currentColor == originalColor;
}

void Tool::fillImageAtPosition(QImage& image, QPoint point){
    QColor fillColor = brushPen.color();
    QColor originalColor = image.pixel(point);
    queue<QPoint> fillQueue = queue<QPoint>();
    vector<QPoint> visited = vector<QPoint>();
    fillQueue.push(point);
    visited.push_back(point);

    while (!fillQueue.empty()) {
        QPoint currentPoint = fillQueue.front();
        QColor currentColor = image.pixel(currentPoint);
        fillQueue.pop();

        image.setPixelColor(currentPoint, fillColor);
        QPoint tmpPoint = currentPoint;
        tmpPoint.rx() -= 1;
        if (tmpPoint.rx() >= 0 && isValid(visited, tmpPoint, currentColor, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.push_back(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.rx() += 1;
        if (tmpPoint.rx() < image.width() && isValid(visited, tmpPoint, currentColor, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.push_back(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() += 1;
        if (tmpPoint.ry() < image.height() && isValid(visited, tmpPoint, currentColor, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.push_back(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() -= 1;
        if (tmpPoint.ry() >= 0 && isValid(visited, tmpPoint, currentColor, originalColor)) {
            fillQueue.push(tmpPoint);
            visited.push_back(tmpPoint);
        }
    }
}

ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

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
        int x = distance * (1 + sin(angle));
        int y = distance * (1 + cos(angle));
        color.setAlphaF(rng->bounded(0.7));
        texture.setPixelColor(x, y, color);
    }

    return texture;
}

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
