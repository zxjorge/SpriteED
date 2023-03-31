#include "frame.h"
#include "ui_frame.h"

Frame::Frame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
}

Frame::~Frame()
{
    delete ui;
}

void Frame::drawImage(QImage image){
    // Convert the QImage to a QPixmap.
    QPixmap pixmap = QPixmap::fromImage(image);
    // Set the QPixmap as the pixmap of the QLabel.
    ui->label->setPixmap(pixmap);
}
