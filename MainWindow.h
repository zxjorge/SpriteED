/**
 * mainwindow.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * The main window of our application
 * Reviewed by: George Benyeogor
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
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
#include <QVBoxLayout>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow of our application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Tool* tool, AnimationFrames* frames, QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    QAction* action;
    QDialog inputBox;
    QSpinBox *heightSpinBox;
    QSpinBox *widthSpinBox;
    QPushButton *okButton;
    QLabel *heightLabel;
    QLabel *inputLabel;
    QLabel *widthLabel;
    QVBoxLayout *inputLayout;
    QHBoxLayout *heightLayout;
    QHBoxLayout *widthLayout;
    QHBoxLayout *buttonLayout;
    AnimationFrames* frames;
    void closeEvent(QCloseEvent* event);
};
#endif // MAINWINDOW_H
