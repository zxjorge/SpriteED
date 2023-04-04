#include "framesviewer.h"
#include "ui_framesviewer.h"

/*
 * NajMingle: 
 * CS3505
 * A7: Sprite Editor
 * 
 */

/// @brief 
/// @param parent 
FramesViewer::FramesViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramesViewer),
    isAnimating(false)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(ui->scrollArea);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->scrollAreaWidgetContents_2->setLayout(layout);

    connect(ui->addButton,
            &QPushButton::clicked,
            this,
            &FramesViewer::addFrame);

    connect(ui->playButton,
            &QPushButton::clicked,
            this,
            &FramesViewer::playButtonPressed);
}

/// @brief 
FramesViewer::~FramesViewer()
{
    delete ui;
}

/// @brief 
void FramesViewer::addFrame(){
    if (isAnimating) {
        return;
    }
    Frame* frame = new Frame(this);

    connect(frame,
            &Frame::sendID,
            this,
            &FramesViewer::setFrame);

    connect(frame,
            &Frame::updateFrameLabel,
            this,
            &FramesViewer::setFrameLabel);

    connect(frame,
            &Frame::deleteFrameClicked,
            this,
            &FramesViewer::deleteFrame);

    frame->setFixedHeight(100); // Set the height to a fixed value
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(frame);
    frames.push_back(frame);
    QImage image = animationF->addFrame();
    frame->setFrameID(animationF->getSelectedIndex());
    frame->drawImage(image);
    connect(frame,&Frame::deleteFrameClicked, this, &FramesViewer::deleteFrame);
    ui->label->setText("Sprite (" + QString::number(frame->getFrameID() + 1) + " of " + QString::number(frames.size()) + ")");
}

/// @brief 
/// @param frame 
void FramesViewer::deleteFrame(Frame *frame) {
    if (isAnimating) {
        return;
    }
    layout->removeWidget(frame);
    auto it = std::find(frames.begin(), frames.end(), frame);
    if (it != frames.end()) {
        frames.erase(it);
    }
}

/// @brief
/// @param id
void FramesViewer::setFrame(int id) {
    if (isAnimating) {
        return;
    }
    ui->label->setText("Sprite (" + QString::number(id + 1)  + " of " + QString::number(frames.size()) + ")");
    animationF->setSelectedIndex(id);
    emit updateSprite();
}

/// @brief 
/// @param id 
void FramesViewer::setFrameLabel(int id){
    if (isAnimating) {
        return;
    }
    frames.erase(frames.begin() + id);
    animationF->removeFrame(id);
    ui->label->setText("Sprite (" + QString::number(id)  + " of " + QString::number(frames.size()) + ")");
    animationF->setSelectedIndex(id - 1);
    emit updateSprite();
}

/// @brief 
void FramesViewer::onFrameDrawnOn() {
    frames.at(animationF->getSelectedIndex())->drawImage(animationF->getSelectedFrame());
}

/// @brief 
/// @param animationF 
void FramesViewer::setAnimFrames(AnimationFrames* animationF) {
    this->animationF = animationF;
    connect(ui->fpsSlider,
            &QSlider::valueChanged,
            animationF,
            &AnimationFrames::setFPS);
    connect(ui->fpsSpinBox,
            &QSpinBox::valueChanged,
            animationF,
            &AnimationFrames::setFPS);
    addFrame();
}

void FramesViewer::fpsChanged(int newFPS) {
    animationF->setFPS(newFPS);
}

void FramesViewer::playButtonPressed() {
    if (isAnimating) {
        animationF->stopAnimation();
        isAnimating = false;
    } else {
        animationF->startAnimation();
        isAnimating = true;
    }
}
