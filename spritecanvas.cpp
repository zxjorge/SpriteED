#include "spritecanvas.h"
#include "ui_spritecanvas.h"

SpriteCanvas::SpriteCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteCanvas)
{
    ui->setupUi(this);
}

SpriteCanvas::~SpriteCanvas()
{
    delete ui;
}
