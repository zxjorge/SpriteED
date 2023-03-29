#ifndef ANIMATIONFRAMES_H
#define ANIMATIONFRAMES_H

#include <QObject>
#include <vector>

using std::vector;

class AnimationFrames
{
public:
    AnimationFrames();
    QImage* addFrame();
    QImage* getFrame(int index);
    void deleteFrame(int index);
    int getFrameCount();
private:
    vector<QImage> frames;
};

#endif // ANIMATIONFRAMES_H
