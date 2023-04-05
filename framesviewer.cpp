/**
* framesviewer.cpp made by Najmingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
* This cpp file uses framesviewer.h header file and implements all its methods.
*/
#include "framesviewer.h"
#include "ui_framesviewer.h"

/**
 * @brief FramesViewer::FramesViewer Constructor for the FramesViewer object.
 * @param parent widget that is used to help handle memory and resources.
 */
FramesViewer::FramesViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramesViewer),
    isAnimating(false)
{
    ui->setupUi(this);

    //sets the layout of the framesviewer to accomodate all frames properly.
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

/**
 * @brief FramesViewer::~FramesViewer destructor for the framesviewer object.
 */
FramesViewer::~FramesViewer()
{
    delete ui;
}

/**
 * @brief FramesViewer::addFrame adds a frame to framesviewer
 */
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
            &Frame::deleteFrameClicked,
            this,
            &FramesViewer::deleteFrame);

    //sets the hight to a fixed value
    frame->setFixedHeight(100);

    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    //adds frame to the layout and the vector of frames
    layout->addWidget(frame);
    frames.push_back(frame);

    QImage image = animationF->addFrame();
    frame->setFrameID(animationF->getSelectedIndex());
    frame->drawImage(image);
    ui->label->setText("Sprite (" + QString::number(frame->getFrameID() + 1) + " of " + QString::number(frames.size()) + ")");
}

/**
 * @brief FramesViewer::deleteFrame method that deletes the frame from the framesviewer
 * @param Id This is the id of the frame to be deleted
 */
void FramesViewer::deleteFrame(int id) {
    if (isAnimating) {
        return;
    }
    Frame* frame = frames[id];

    if(frames.size() == 1){
        animationF->clear();
        frame->drawImage(animationF->getSelectedFrame());
    }else{

        frames.erase(frames.begin() + id);
        animationF->removeFrame(id);

        //Handles changing the sprite label when deleting the first frame in the vector
        if(id != 0){
            ui->label->setText("Sprite (" + QString::number(id)  + " of " + QString::number(frames.size()) + ")");
        }
        else{
            ui->label->setText("Sprite (" + QString::number(id + 1)  + " of " + QString::number(frames.size()) + ")");
        }

        //Handles changing the selected index when deleting the first frame in the vector
        if(id != 0){
            animationF->setSelectedIndex(id - 1);
        }else{
            animationF->setSelectedIndex(id);
        }

        layout->removeWidget(frame);

        //finds the frame from the frames vector and deletes it
        auto it = std::find(frames.begin(), frames.end(), frame);
        if (it != frames.end()) {
            frames.erase(it);
        }
        delete frame;

        //updates frame ids to make sure they're all indexed properly
        updateFrameIDs();
    }
    emit updateSprite();
}


/**
 * @brief FramesViewer::deleteFrame method that deletes the frame from the framesviewer
 * @param Id This is the id of the frame to be deleted
 */
void FramesViewer::deleteAllFrames() {
    if (isAnimating) {
        return;
    }
    for(int id = 0; id<animationF->getFrameCount();id++){
        Frame* frame = frames[id];

        if(frames.size() == 1){
            animationF->clear();
            frame->drawImage(animationF->getSelectedFrame());
        }else{

            frames.erase(frames.begin() + id);
            animationF->removeFrame(id);

            //Handles changing the sprite label when deleting the first frame in the vector
            if(id != 0){
                ui->label->setText("Sprite (" + QString::number(id)  + " of " + QString::number(frames.size()) + ")");
            }
            else{
                ui->label->setText("Sprite (" + QString::number(id + 1)  + " of " + QString::number(frames.size()) + ")");
            }

            //Handles changing the selected index when deleting the first frame in the vector
            if(id != 0){
                animationF->setSelectedIndex(id - 1);
            }else{
                animationF->setSelectedIndex(id);
            }

            layout->removeWidget(frame);

            //finds the frame from the frames vector and deletes it
            auto it = std::find(frames.begin(), frames.end(), frame);
            if (it != frames.end()) {
                frames.erase(it);
            }
            delete frame;

            //updates frame ids to make sure they're all indexed properly
            updateFrameIDs();
        }
        emit updateSprite();
    }
}
/**
 * @brief FramesViewer::setFrame sets the frame
 * @param id this is the id of the frame to be set
 */
void FramesViewer::setFrame(int id){
    if (isAnimating) {
        return;
    }

    ui->label->setText("Sprite (" + QString::number(id + 1)  + " of " + QString::number(frames.size()) + ")");
    animationF->setSelectedIndex(id);
    emit updateSprite();
}


/**
 * @brief FramesViewer::onFrameDrawnOn
 */
void FramesViewer::onFrameDrawnOn() {
    frames.at(animationF->getSelectedIndex())->drawImage(animationF->getSelectedFrame());
}

/**
 * @brief FramesViewer::setAnimFrames sets the animation settings (FPS)
 * @param animationF the animation frame
 */
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

/**
 * @brief FramesViewer::fpsChanged sets the FPS of the amimation to a new value (provided in parameter)
 * @param newFPS the new value of the FPS to be set for the animation
 */
void FramesViewer::fpsChanged(int newFPS) {
    animationF->setFPS(newFPS);
}

/**
 * @brief FramesViewer::playButtonPressed handles what happens when the play/pause button is pressed
 */
void FramesViewer::playButtonPressed() {
    if (isAnimating) {
        animationF->stopAnimation();
        isAnimating = false;
        ui->playButton->setText("Play");
    } else if(frames.size()>1){
        animationF->startAnimation();
        isAnimating = true;
        ui->playButton->setText("Pause");
    }
}




/**
 * @brief FramesViewer::updateFrameIDs updates the frames' ids to make sure
 * they're all indexed properly
 */
void FramesViewer::updateFrameIDs(){
    for (int i = frames.size() - 1; i >= 0; i--) {
        frames[i]->setFrameID(i);
    }
}

