#include "spritecanvas.h"
#include "ui_spritecanvas.h"
#include <iostream>
#include <cmath>
#include <QPainter>

SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas),
    frames(nullptr)
{
    ui->setupUi(this);
}

SpriteCanvas::~SpriteCanvas()
{
    delete ui;
}

void SpriteCanvas::setTool(Tool* tool) {
    this->tool = tool;
    showBrushIcon();
}

void SpriteCanvas::setAnimFrames(AnimationFrames* frames) {
    this->frames = frames;
    sprite = frames->getSelectedFrame();
    update();
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
    tool->drawPointOnImage(sprite, pos);
    lastMousePos = pos;
    update();
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) {
        return;
    }

    QPoint pos = getScaledMousePoint(event);
    tool->drawLineOnImage(sprite, lastMousePos, pos);
    lastMousePos = pos;
    update();
}

void SpriteCanvas::mouseReleaseEvent(QMouseEvent*) {
    frames->updateSelectedFrame(sprite);
}

void SpriteCanvas::showAirBrushIcon(){
    QPixmap brushPixmap(":/icons/airbrush_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
}

void SpriteCanvas::showFillIcon(){
    QPixmap brushPixmap(":/icons/filltool_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);

}

void SpriteCanvas::showEraseIcon(){
    QPixmap brushPixmap(":/icons/erase_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 2, scaledBrushPixmap.height() / 2);
    setCursor(brushCursor);
}

void SpriteCanvas::showBrushIcon(){
    QPixmap brushPixmap(":/icons/brush_icon .png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, 0, scaledBrushPixmap.height());
    setCursor(brushCursor);
}
