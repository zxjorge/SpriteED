#include "animationframes.h"
#include "ui_brushproperties.h"

/// @brief 
/// @param parent 
AnimationFrames::AnimationFrames(QWidget *parent) :
    QWidget(parent),
    frames(vector<QImage>()),
    width(192),
    height(128),
    selectedIndex(0)
{
}

/// @brief 
/// @return 
QImage AnimationFrames::addFrame()
{
    if(frames.size() > 0){
        selectedIndex++;
    }
    QImage img = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    frames.push_back(img);
    return img;
}

/// @brief 
/// @return 
QImage AnimationFrames::getSelectedFrame()
{
    return frames.at(selectedIndex);
}

/// @brief 
/// @param index 
void AnimationFrames::deleteFrame(int index)
{
    frames.erase(frames.begin() + index);
    if (frames.empty()) {
        addFrame();
    }
}

/// @brief 
/// @return 
int AnimationFrames::getFrameCount()
{
    return frames.size();
}

/// @brief 
void AnimationFrames::clear() {
    frames.clear();
    addFrame();
}

/// @brief 
/// @param image 
void AnimationFrames::updateSelectedFrame(QImage image) {
    // Replace image at selectedIndex
    frames.at(selectedIndex) = image;
}

/// @brief 
/// @param index 
void AnimationFrames::setSelectedIndex(int index){
    this->selectedIndex = index;
}

/// @brief 
/// @return 
int AnimationFrames::getSelectedIndex(){
    return selectedIndex;
}

/// @brief 
void AnimationFrames::clearSelectedFrame() {
    frames.at(selectedIndex).fill(Qt::white);
}
