#ifndef CANVASMAINWINDOW_H
#define CANVASMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CanvasMainWindow; }
QT_END_NAMESPACE

class CanvasMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CanvasMainWindow(QWidget *parent = nullptr);
    ~CanvasMainWindow();

private:
    Ui::CanvasMainWindow *ui;
};
#endif // CANVASMAINWINDOW_H
