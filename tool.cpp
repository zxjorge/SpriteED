#include <queue>
#include <vector>
#include "tool.h"
#include <algorithm>

using std::queue;
using std::vector;

Tool::Tool() :
    brushPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
    selectedToolType(ToolType::BRUSH)
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

void Tool::fillImageAtPosition(QImage& image, QPoint point){
    QColor fillColor = brushPen.color();
    QColor originalColor = image.pixel(point);
    queue<QPoint> fillQueue = queue<QPoint>();
    vector<QPoint> visited = vector<QPoint>();
    fillQueue.push(point);

    while (!fillQueue.empty()) {
        QPoint currentPoint = fillQueue.front();
        QColor currentColor = image.pixel(currentPoint);
        fillQueue.pop();

        if (currentColor != originalColor) {
            continue;
        }
        if (std::find(visited.begin(), visited.end(), currentPoint) != visited.end()) {
            continue;
        }

        visited.push_back(currentPoint);
        image.setPixelColor(currentPoint, fillColor);
        QPoint tmpPoint = currentPoint;
        tmpPoint.rx() -= 1;
        if (tmpPoint.rx() >= 0) {
            fillQueue.push(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.rx() += 1;
        if (tmpPoint.rx() < image.width()) {
            fillQueue.push(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() += 1;
        if (tmpPoint.ry() < image.height()) {
            fillQueue.push(tmpPoint);
        }
        tmpPoint = currentPoint;
        tmpPoint.ry() -= 1;
        if (tmpPoint.ry() >= 0) {
            fillQueue.push(tmpPoint);
        }
    }
}

QPen Tool::getBrushPen(){
    return brushPen;
}

ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}

QPen Tool::getAirBrushPen() {
    QPen pen = brushPen;

    // TODO Random texture for pen

    return pen;
}

QPen Tool::getErasePen() {
    QPen erasePen = brushPen;
    erasePen.setColor(Qt::white);
    return erasePen;
}
