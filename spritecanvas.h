#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "brush.h"
#include "brushproperties.h"
#include <QPixmap>
#include <QCursor>


enum DimensionLimit { WIDTH, HEIGHT };

namespace Ui {
class SpriteCanvas;
}

class SpriteCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteCanvas(QWidget *parent = nullptr);
    ~SpriteCanvas();

    void showEraseIcon();
    void showFillIcon();
    void showAirBrushIcon();
    void showBrushIcon();

private:
    Ui::SpriteCanvas *ui;

    QImage sprite;
    QPoint lastMousePos;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    float getPixelSize();
    QPoint getScaledMousePoint(QMouseEvent *event);
    DimensionLimit getDimensionLimit();

};

#endif // SPRITECANVAS_H
