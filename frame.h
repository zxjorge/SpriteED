#ifndef FRAME_H
#define FRAME_H
#include <QImage>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class Frame;
}

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();
    void drawImage(QImage image);

private:
    Ui::Frame *ui;
};

#endif // FRAME_H
