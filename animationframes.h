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
    QImage getSelectedFrame();
    void updateSelectedFrame(QImage image);
    void deleteFrame(int index);
    int getFrameCount();
    void clear();

private:
    vector<QImage> frames;
    int width;
    int height;
    int selectedIndex;

public slots:
     void clearSelectedFrame();
};

#endif // ANIMATIONFRAMES_H
