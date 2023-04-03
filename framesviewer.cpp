#include "framesviewer.h"
#include "ui_framesviewer.h"

/// @brief 
/// @param parent 
FramesViewer::FramesViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramesViewer)
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
}

/// @brief 
FramesViewer::~FramesViewer()
{
    delete ui;
}

/// @brief 
void FramesViewer::addFrame(){
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
    layout->removeWidget(frame);
    auto it = std::find(frames.begin(), frames.end(), frame);
    if (it != frames.end()) {
        frames.erase(it);
    }
}

/// @brief
/// @param id
void FramesViewer::setFrame(int id){
    ui->label->setText("Sprite (" + QString::number(id + 1)  + " of " + QString::number(frames.size()) + ")");
    animationF->setSelectedIndex(id);
    emit updateSprite();
}

/// @brief 
/// @param id 
void FramesViewer::setFrameLabel(int id){
    frames.erase(frames.begin() + id);
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
}
