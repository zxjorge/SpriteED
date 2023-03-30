#ifndef FRAMESVIEWER_H
#define FRAMESVIEWER_H
#include "frame.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QSize>

namespace Ui {
class FramesViewer;
}

class FramesViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FramesViewer(QWidget *parent = nullptr);
    ~FramesViewer();
    void addFrame();

private:
    Ui::FramesViewer *ui;
    QVBoxLayout* layout;
};

#endif // FRAMESVIEWER_H
