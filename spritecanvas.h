#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H
class SpriteCanvas : public QWidget
{
    Q_OBJECT

public:
    SpriteCanvas(QWidget *parent = nullptr);

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

#endif // SPRITECANVAS_H
