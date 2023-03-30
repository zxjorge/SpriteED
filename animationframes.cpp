#include "animationframes.h"

AnimationFrames::AnimationFrames() :
    frames(vector<QImage>()),
    width(64),
    height(64),
    selectedIndex(0)
{
    addFrame();
}


QImage AnimationFrames::addFrame()
{
    QImage img = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    frames.push_back(img);
    return img;
}

QImage AnimationFrames::getSelectedFrame()
{
    return frames.at(selectedIndex);
}

void AnimationFrames::deleteFrame(int index)
{
    frames.erase(frames.begin() + index);
    if (frames.empty()) {
        addFrame();
    }
}

int AnimationFrames::getFrameCount()
{
    return frames.size();
}

void AnimationFrames::clear() {
    frames.clear();
    addFrame();
}

void AnimationFrames::updateSelectedFrame(QImage image) {
    // Replace image at selectedIndex
    frames.at(selectedIndex) = image;
}
