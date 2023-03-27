#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

#ifndef MYCANVAS_H
#define MYCANVAS_H
class MyCanvas : public QWidget
{
    Q_OBJECT

public:
    MyCanvas(QWidget *parent = nullptr);

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_isDrawing;
    QPoint m_lastPoint;
    QImage m_image;
};

#endif // MYCANVAS_H
