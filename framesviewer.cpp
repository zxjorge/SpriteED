#include "framesviewer.h"
#include "ui_framesviewer.h"

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
    Frame* frame = new Frame(nullptr);
    frame->setFixedHeight(100); // Set the height to a fixed value
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(frame);
    frames.push_back(frame);
    animationF->addFrame();
    QImage image = animationF->getSelectedFrame();
    frame->drawImage(image);
}

/// @brief 
/// @param animationF 
void FramesViewer::setAnimFrames(AnimationFrames* animationF) {
    this->animationF = animationF;
}
