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
    explicit Frame(QWidget *parent);
    ~Frame();
    void drawImage(QImage image);
    void deleteFrame();
    void sendFrame();
    void setFrameID(int id);
    int getFrameID();

signals:
    void deleteFrameClicked(Frame * frame);
    void sendID(int id);
    void updateFrameLabel(int id);

private:
    Ui::Frame *ui;
    int frameID;
};

#endif // FRAME_H
