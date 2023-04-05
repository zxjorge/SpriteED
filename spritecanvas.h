/**
 * spritecanvas.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * This header file will be used by spritecanvas.cpp and has methods, signals, and slots to handle
 * the logic and data for the spritecanvas, which is where the user would draw on the sprite editor UI.
 */
#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include "tool.h"
#include "animationframes.h"

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
    void setTool(Tool* tool);
    void setAnimFrames(AnimationFrames* frames);

signals:
    void frameDrawnOn();

public slots:
    void updateSprite();
    void onExternalFrameUpdate();
    void setResized(bool value);

private:
    Ui::SpriteCanvas *ui;

    QImage sprite;
    QPoint lastMousePos;
    Tool* tool;
    AnimationFrames* frames;
    bool resized;
    int canvasOffsetX;
    int canvasOffsetY;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    float getPixelSize();
    QPoint getScaledMousePoint(QMouseEvent *event);
    DimensionLimit getDimensionLimit();

};

#endif // SPRITECANVAS_H
