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

FramesViewer::~FramesViewer()
{
    delete ui;
}

void FramesViewer::addFrame(){
    Frame* frame = new Frame(nullptr);
    frame->setFixedHeight(100); // Set the height to a fixed value
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //    ui->scrollArea->widget()->layout()->addWidget(frame);
    layout->addWidget(frame);
}
