#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include "tool.h"
#include "animationframes.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Tool* tool, AnimationFrames* frames, QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QAction* action;
};
#endif // MAINWINDOW_H
