#include "frame.h"
#include "ui_frame.h"

/*
 * NajMingle:
 * CS3505
 * A7: Sprite Editor
 *
 */

/// @brief
/// @param parent
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

/// @brief
Frame::~Frame()
{
    delete ui;
}

/// @brief
/// @param image
void Frame::drawImage(QImage image){
    QSize size = QSize(75, 75);
    QPixmap pixmap(size);
    pixmap.convertFromImage(image);
    ui->frame->setIcon(QIcon(pixmap));
    ui->frame->setIconSize(size);
}

/// @brief 
void Frame::deleteFrame() {
    emit updateFrameLabel(frameID);
    emit deleteFrameClicked(this);
}

/// @brief 
void Frame::sendFrame() {
    emit sendID(frameID);
}

/// @brief 
/// @param id 
void Frame::setFrameID(int id){
    frameID = id;
}

/// @brief 
/// @return 
int Frame::getFrameID(){
    return frameID;
}
