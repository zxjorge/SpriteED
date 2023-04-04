/**
* frame.cpp made by Najmingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
* This cpp file uses frame.h header file and implements all its methods.
*/
#include "frame.h"
#include "ui_frame.h"

/**
 * @brief Frame::Frame This is the constructor for a frame object.
 * @param parent widget that is used to help handle memory and resources.
 */
Frame::Frame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);

    connect(ui->deleteButton,
            &QPushButton::clicked,
            this,
            &Frame::deleteFrame);

    connect(ui->frame,
            &QPushButton::clicked,
            this,
            &Frame::sendFrame);
}

/**
 * @brief Frame::~Frame Destructor for Frame.
 */
Frame::~Frame()
{
    delete ui;
}

/**
 * @brief Frame::drawImage sets a preview of the canvas drawing into the frame's window.
 * @param image image that is to be previewed on the frame.
 */
void Frame::drawImage(QImage image){
    QSize size = QSize(75, 75);
    QPixmap pixmap(size);
    pixmap.convertFromImage(image);
    ui->frame->setIcon(QIcon(pixmap));
    ui->frame->setIconSize(size);
}

/**
 * @brief Frame::deleteFrame emits two signals which eventually result.
 * in the deletion of the frame widget from the framesviewer.ui
 */
void Frame::deleteFrame() {
    emit updateFrameLabel(frameID);
    emit deleteFrameClicked(this);
}

/**
 * @brief Frame::sendFrame emits a signal that sends the frame's ID.
 */
void Frame::sendFrame() {
    emit sendID(frameID);
}

/**
 * @brief Frame::setFrameID sets the ID of the frame.
 * @param id this is the id that is set to the frame.
 */
void Frame::setFrameID(int id){
    frameID = id;
}

/**
 * @brief Frame::getFrameID returns frame's id.
 * @return int which is the id of the frame.
 */
int Frame::getFrameID(){
    return frameID;
}
