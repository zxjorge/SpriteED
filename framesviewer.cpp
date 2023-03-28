#include "framesviewer.h"
#include "ui_framesviewer.h"

FramesViewer::FramesViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramesViewer)
{
    ui->setupUi(this);
}

FramesViewer::~FramesViewer()
{
    delete ui;
}
