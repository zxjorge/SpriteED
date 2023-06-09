/**
 * framesviewer.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * This header file will be used by framesviewer.cpp and has methods, signals, and slots to handle
 * the logic and data in regards to how the frames are viewed on the UI, and for the animation's
 * play, pause, and fps sliders on the sprite editor.
 * Reviewed by: Sahil Karki
 */
#ifndef FRAMESVIEWER_H
#define FRAMESVIEWER_H
#include "frame.h"
#include "animationframes.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QSize>
#include <vector>
#include <QImage>

namespace Ui {
class FramesViewer;
}

/**
 * @brief The FramesViewer class where all the frames are shown
 */
class FramesViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FramesViewer(QWidget *parent = nullptr);
    ~FramesViewer();
    void setAnimFrames(AnimationFrames* animationF);

private:
    Ui::FramesViewer *ui;
    QVBoxLayout* layout;
    AnimationFrames* animationF;
    vector<Frame*> frames;
    bool isAnimating;
    void updateFrameIDs();
    void deleteAllFramesPrivate(bool keepOne, bool uiOnly);
    void deleteFramePrivate(int id, bool keepOne, bool uiOnly);

signals:
    void updateSprite();


public slots:
   void deleteAllFrames();
   void onFrameDrawnOn();
   void onProjectLoaded();
   void deleteFrame(int id);

private slots:
    void setFrame(int id);
    void fpsChanged(int newFPS);
    void playButtonPressed();
    void addFrame();

};

#endif // FRAMESVIEWER_H
