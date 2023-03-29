#include "spritecanvas.h"
#include "ui_spritecanvas.h"
#include <iostream>
#include <cmath>

SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas)
{
    ui->setupUi(this);
    sprite = QImage(16, 24, QImage::Format_ARGB32_Premultiplied);
    sprite.fill(Qt::white);
}

SpriteCanvas::~SpriteCanvas()
{
    delete ui;
}

void SpriteCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush = QBrush(Qt::BrushStyle::SolidPattern);
    int pixelSize = getPixelSize();

    for (int x = 0; x < sprite.width(); x++) {
        for (int y = 0; y < sprite.height(); y++) {
            brush.setColor(sprite.pixelColor(x, y));
            painter.fillRect(
                x * pixelSize,
                y * pixelSize,
                pixelSize,
                pixelSize,
                brush
            );
        }
    }
}

float SpriteCanvas::getPixelSize() {
    if ((float)width() / height() < (float)sprite.width() / sprite.height()) {
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

    sprite.setPixelColor(pos, Qt::red);
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
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastMousePos, pos);
    lastMousePos = pos;
    update();
}
