#include "SpriteCanvas.h"

SpriteCanvas::SpriteCanvas(QWidget *parent)
    : QWidget(parent)
{
    m_isDrawing = false;
    m_image = QImage(80, 60, QImage::Format_ARGB32_Premultiplied);
    m_image.fill(Qt::white);
    setMinimumSize(400, 400);
}

void SpriteCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, 800, 600), m_image);
}

void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_lastPoint = event->pos() * 0.1;
    }
}

void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawing) {
        QPainter painter(&m_image);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(m_lastPoint, event->pos() * 0.1);
        m_lastPoint = event->pos() * 0.1;
        update();
    }
}

void SpriteCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;
    }
}
