#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class SpriteCanvas;
}

class SpriteCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteCanvas(QWidget *parent = nullptr);
    ~SpriteCanvas();

private:
    Ui::SpriteCanvas *ui;

    QImage sprite;
    QPoint lastMousePos;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    float getPixelSize();
    QPoint getScaledMousePoint(QMouseEvent *event);
};

#endif // SPRITECANVAS_H
