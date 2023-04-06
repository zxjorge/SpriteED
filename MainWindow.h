#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include "tool.h"
#include "animationframes.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Tool* tool, AnimationFrames* frames, QWidget *parent = nullptr);
    ~MainWindow();
    void askForCanvasSize();

signals:
    void openClicked(QString);
    void saveAsClicked(QString);
    void saveClicked(QString);
private slots:
    void HelpTriggered();
    void OpenTriggered();
    void saveAsTriggered();
    void saveTriggered();
    void saveFileError();
    void loadFileError();
    void storeValue(QString value);

private:
    Ui::MainWindow *ui;
    QAction* action;
    QString m_value;

};
#endif // MAINWINDOW_H
