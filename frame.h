#ifndef FRAME_H
#define FRAME_H

#include <QWidget>

namespace Ui {
class Frame;
}

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();

private:
    Ui::Frame *ui;
};

#endif // FRAME_H
