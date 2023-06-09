/**
 * frame.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * This header file will be used by frame.cpp and has methods, signals, and slots to handle
 * all the frame widget data and logic of the sprite editor.
 * Reviewed by: George Benyeogor
 */

#ifndef FRAME_H
#define FRAME_H
#include <QImage>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class Frame;
}

/**
 * @brief The Frame widget, which is used in FramesViewer to represent each frame
 */
class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent);
    ~Frame();
    void drawImage(QImage image);
    void deleteFrame();
    void sendFrame();
    void setFrameID(int id);
    int getFrameID();

signals:
    void deleteFrameClicked(int id);
    void sendID(int id);
    void updateFrameLabel(int id);

private:
    Ui::Frame *ui;
    int frameID;
};

#endif // FRAME_H
