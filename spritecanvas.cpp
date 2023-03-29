#include "spritecanvas.h"
#include "ui_spritecanvas.h"
#include <iostream>
#include <cmath>
#include <QPainter>

SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas)
{
    ui->setupUi(this);
    sprite = QImage(24, 16, QImage::Format_ARGB32_Premultiplied);
    sprite.fill(Qt::white);

}

SpriteCanvas::~SpriteCanvas()
{
    delete ui;
}

void SpriteCanvas::setTool(Tool* tool) {
    this->tool = tool;
}

void SpriteCanvas::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    float scale;
    if (getDimensionLimit() == DimensionLimit::WIDTH) {
        scale = (float)width() / sprite.width();
    } else {
        scale = (float)height() / sprite.height();
    }
    painter.drawImage(
        0,
        0,
        sprite.scaled(
            sprite.width() * scale,
            sprite.height() * scale,
            Qt::IgnoreAspectRatio,
            Qt::FastTransformation
        )
    );
}
DimensionLimit SpriteCanvas::getDimensionLimit() {
    if ((float)width() / height() < (float)sprite.width() / sprite.height()) {
        return DimensionLimit::WIDTH;
    } else {
        return DimensionLimit::HEIGHT;
    }
}

float SpriteCanvas::getPixelSize() {
    if (getDimensionLimit() == DimensionLimit::WIDTH) {
        return (float)width() / sprite.width();
    } else {
        return (float)height() / sprite.height();
    }
}

QPoint SpriteCanvas::getScaledMousePoint(QMouseEvent* event) {
    QPointF point = event->position();
    point /= getPixelSize();
    // Offset to pixel centers instead of corners
    point.rx() = point.x() - 0.5;
    point.ry() = point.y() - 0.5;
    return point.toPoint();
}

void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    QPoint pos = getScaledMousePoint(event);
    if(tool->getSelectedToolType() == ERASER)
        sprite.setPixelColor(pos,Qt::white);
    else
        sprite.setPixelColor(pos, tool->getFillColor());
    lastMousePos = pos;
    update();
 }

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) {
        return;
    }

    QPoint pos = getScaledMousePoint(event);

    QPainter painter(&sprite);
    if(tool->getSelectedToolType() == ERASER)
        painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
        painter.setPen(QPen(tool->getFillColor(), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastMousePos, pos);
    lastMousePos = pos;
    update();
}


void SpriteCanvas::showAirBrushIcon(){
    QPixmap brushPixmap(":/icons/airbrush_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
    tool->setSelectedToolType(AIRBRUSH);
}
void SpriteCanvas::showFillIcon(){
    QPixmap brushPixmap(":/icons/filltool_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
    tool->setSelectedToolType(FILL);

}
void SpriteCanvas::showEraseIcon(){
    QPixmap brushPixmap(":/icons/erase_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
    tool->setSelectedToolType(ERASER);
}
void SpriteCanvas::showBrushIcon(){
    QPixmap brushPixmap(":/icons/brush_icon .png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, 0, scaledBrushPixmap.height());
    setCursor(brushCursor);
    tool->setSelectedToolType(BRUSH);
}






