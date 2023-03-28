#ifndef SPRITECANVAS_H
#define SPRITECANVAS_H

#include <QWidget>

namespace Ui {
class SpriteCanvas;
}

class SpriteCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteCanvas(QWidget *parent = nullptr);
    ~SpriteCanvas();

private:
    Ui::SpriteCanvas *ui;
};

#endif // SPRITECANVAS_H
