/**
* spritecanvas.cpp made by Najmingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
* This cpp file uses spritecanvas.h header file and implements all its methods.
*/
#include "spritecanvas.h"
#include "ui_spritecanvas.h"
#include <iostream>
#include <cmath>
#include <QPainter>

/**
 * @brief SpriteCanvas::SpriteCanvas constructor for spriteCanvas.
 * @param parent
 */
SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas)
{
    ui->setupUi(this);
}

/**
 * @brief SpriteCanvas::~SpriteCanvas destructor for spriteCanvas.
 */
SpriteCanvas::~SpriteCanvas()
{
    delete ui;
}

/**
 * @brief SpriteCanvas::setTool sets the tool on the sprite canvas to be the one which is
 * highlighted amongst the tool buttons.
 * @param tool tool to be set.
 */
void SpriteCanvas::setTool(Tool* tool) {
    this->tool = tool;
    showBrushIcon();
}

/**
 * @brief SpriteCanvas::setAnimFrames sets the animation frames
 * @param frames frames in animation
 */
void SpriteCanvas::setAnimFrames(AnimationFrames* frames) {
    this->frames = frames;
    sprite = frames->getSelectedFrame();
    update();
}

/**
 * @brief SpriteCanvas::onExternalFrameUpdate updates the sprite canvas to be the selected frame.
 */
void SpriteCanvas::onExternalFrameUpdate() {
    sprite = frames->getSelectedFrame();
    update();
}

/**
 * @brief SpriteCanvas::updateSprite updates the sprite canvas to be the selected frame.
 */
void SpriteCanvas::updateSprite(){
    sprite = frames->getSelectedFrame();
    update();
}

/**
 * @brief SpriteCanvas::paintEvent
 */
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

/**
 * @brief SpriteCanvas::getDimensionLimit gets the dimensions of the sprite canvas
 * @return the width and the height of the sprite canvas
 */
DimensionLimit SpriteCanvas::getDimensionLimit() {
    if ((float)width() / height() < (float)sprite.width() / sprite.height()) {
        return DimensionLimit::WIDTH;
    } else {
        return DimensionLimit::HEIGHT;
    }
}

/**
 * @brief SpriteCanvas::getPixelSize returns the pixel size of the sprite canvas
 * @return a float value which represents the pixel size
 */
float SpriteCanvas::getPixelSize() {
    if (getDimensionLimit() == DimensionLimit::WIDTH) {
        return (float)width() / sprite.width();
    } else {
        return (float)height() / sprite.height();
    }
}

/**
 * @brief SpriteCanvas::getScaledMousePoint convert the position of the mouse to a QPoint object which is
 * scaled based on the size of the sprite canvas' pixel size
 * @param event this QMouseEvent is used to get the current position of the mouse
 * @return the scaled position of the mouse cursor as a QPoint
 */
QPoint SpriteCanvas::getScaledMousePoint(QMouseEvent* event) {
    QPointF point = event->position();
    point /= getPixelSize();
    // Offset to pixel centers instead of corners
    point.rx() = point.x() - 0.5;
    point.ry() = point.y() - 0.5;
    return point.toPoint();
}

/**
 * @brief SpriteCanvas::mousePressEvent this method is responsible for handling what happens when something is drawn on the spriteCanvas.
 * It updates the canvas based on the current drawing tool and the position of the mouse cursor.
 * @param event this QMouseEvent is used to check if the left button of the mouse is being clicked or not and to get the position.
 */
void SpriteCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || frames->isAnimating()) {
        return;
    }

    QPoint pos = getScaledMousePoint(event);
    tool->drawPointOnImage(sprite, pos);
    lastMousePos = pos;
    update();
}

/**
 * @brief SpriteCanvas::mouseMoveEvent this method is responsible for handling what happens when the mouse is moved on the sprite canvas while the left click is being
 * held down. It updates the canvas based on the current drawing tool and the position of the mouse cursor.
 * @param event this QMouseEvent is used to check if the left button of the mouse is being clicked or not and to get the position.
 */
void SpriteCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton || frames->isAnimating()) {
        return;
    }

    QPoint pos = getScaledMousePoint(event);
    tool->drawLineOnImage(sprite, lastMousePos, pos);
    lastMousePos = pos;
    update();
}

/**
 * @brief SpriteCanvas::mouseReleaseEvent this method is responsible for handling what happens when the mouse button is released on the sprite canvas.
 */
void SpriteCanvas::mouseReleaseEvent(QMouseEvent*) {
    if (frames->isAnimating()) {
        return;
    }
    frames->updateSelectedFrame(sprite);
    emit frameDrawnOn();
}

/**
 * @brief SpriteCanvas::showAirBrushIcon shows the airbrush icon when the cursor is over the sprite canvas
 */
void SpriteCanvas::showAirBrushIcon(){
    QPixmap brushPixmap(":/icons/airbrush_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(55, 55, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 3.5, scaledBrushPixmap.height() / 6 );
    setCursor(brushCursor);
}

/**
 * @brief SpriteCanvas::showFillIcon shows the fill icon when the cursor is over the sprite canvas
 */
void SpriteCanvas::showFillIcon(){
    QPixmap brushPixmap(":/icons/filltool_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width()/2, scaledBrushPixmap.height()/2);
    setCursor(brushCursor);

}

/**
 * @brief SpriteCanvas::showEraseIcon shows the erase icon when the cursor is over the sprite canvas
 */
void SpriteCanvas::showEraseIcon(){
    QPixmap brushPixmap(":/icons/erase_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 6, scaledBrushPixmap.height() / 1.2);
    setCursor(brushCursor);
}

/**
 * @brief SpriteCanvas::showBrushIcon shows the brush icon when the cursor is over the sprite canvas
 */
void SpriteCanvas::showBrushIcon(){
    QPixmap brushPixmap(":/icons/brush_icon.png");
    QPixmap scaledBrushPixmap = brushPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QCursor brushCursor(scaledBrushPixmap, scaledBrushPixmap.width() / 8, scaledBrushPixmap.height()/1.1);
    setCursor(brushCursor);
}
