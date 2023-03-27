#include "mycanvas.h"

MyCanvas::MyCanvas(QWidget *parent)
    : QWidget(parent)
{
    m_isDrawing = false;
    m_image = QImage(800, 600, QImage::Format_ARGB32_Premultiplied);
    m_image.fill(Qt::white);
    setMinimumSize(400, 400);
}

void MyCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_lastPoint = event->pos();
    }
}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawing) {
        QPainter painter(&m_image);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(m_lastPoint, event->pos());
        m_lastPoint = event->pos();
        update();
    }
}

void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;
    }
}
