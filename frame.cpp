#include "frame.h"
#include "ui_frame.h"

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
//    QImage scaledImage = image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation); // scale the image to fit within the pixmap size
    pixmap.convertFromImage(image);
    // Set the QPixmap as the pixmap of the QLabel.
    ui->frame->setIcon(QIcon(pixmap));
    ui->frame->setIconSize(size);
}

void Frame::deleteFrame() {
    emit updateFrameLabel(frameID);
    emit deleteFrameClicked(this);
    delete ui->horizontalLayoutWidget;
}

void Frame::sendFrame() {
    emit sendID(frameID);
}

void Frame::setFrameID(int id){
    frameID = id;
}

int Frame::getFrameID(){
    return frameID;
}



