#include "frame.h"
#include "ui_frame.h"

/// @brief 
/// @param parent 
Frame::Frame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
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
    ui->pushButton->setIcon(QIcon(pixmap));
    ui->pushButton->setIconSize(size);
}
