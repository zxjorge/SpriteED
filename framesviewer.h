#ifndef FRAMESVIEWER_H
#define FRAMESVIEWER_H

#include <QWidget>

namespace Ui {
class FramesViewer;
}

class FramesViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FramesViewer(QWidget *parent = nullptr);
    ~FramesViewer();

private:
    Ui::FramesViewer *ui;
};

#endif // FRAMESVIEWER_H
