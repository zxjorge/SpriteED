#ifndef ANIMATIONFRAMES_H
#define ANIMATIONFRAMES_H

#include <QObject>
#include <vector>
#include <QImage>

using std::vector;

class AnimationFrames
{
public:
    AnimationFrames();
    QImage addFrame();
    QImage getFrame(int index);
    void updateFrame(int index, QImage image);
    void deleteFrame(int index);
    int getFrameCount();
private:
    vector<QImage> frames;
};

#endif // ANIMATIONFRAMES_H
