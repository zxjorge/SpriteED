#include "spritecanvas.h"
#include "ui_spritecanvas.h"
#include <iostream>
#include <algorithm>

SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas)
{
    ui->setupUi(this);
    sprite = QImage(32, 48, QImage::Format_ARGB32_Premultiplied);
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

int SpriteCanvas::getPixelSize() {
    if ((float)width() / height() < (float)sprite.width() / sprite.height()) {
        return width() / sprite.width();
    } else {
        return height() / sprite.height();
    }
}

QPoint mousePointFtoPoint(QPointF point, int pixelSize) {
    point = point / pixelSize;
    return point.toPoint();
}

void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    QPoint pos = mousePointFtoPoint(event->position(), getPixelSize());

    sprite.setPixelColor(pos, Qt::red);
    lastMousePos = pos;
    update();
 }

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) {
        return;
    }

    QPoint pos = mousePointFtoPoint(event->position(), getPixelSize());

    QPainter painter(&sprite);
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastMousePos, pos);
    lastMousePos = pos;
    update();
}
