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

class FramesViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FramesViewer(QWidget *parent = nullptr);
    ~FramesViewer();
    void setAnimFrames(AnimationFrames* animationF);

public:
    void onFrameDrawnOn();
    void deleteFrame(Frame* frame);

private:
    Ui::FramesViewer *ui;
    QVBoxLayout* layout;
    AnimationFrames* animationF;
    vector<Frame*> frames;
    bool isAnimating;

signals:
    void updateSprite();

private slots:
    void setFrame(int id);
    void setFrameLabel(int id);
    void fpsChanged(int newFPS);
    void playButtonPressed();
    void addFrame();
};

#endif // FRAMESVIEWER_H
