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
    void addFrame();
    void setAnimFrames(AnimationFrames* animationF);


private:
    Ui::FramesViewer *ui;
    QVBoxLayout* layout;
    AnimationFrames* animationF;
    vector<Frame*> frames;

};

#endif // FRAMESVIEWER_H
