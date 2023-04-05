#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brushproperties.h"

/*
 * NajMingle: 
 * CS3505
 * A7: Sprite Editor
 * 
 */

/// @brief Constructor for the MainWindow.
/// @param tool Represents the tool which is used to draw/erase on the canvas.
/// @param frames Represents the frames.
/// @param parent 
MainWindow::MainWindow(Tool* tool, AnimationFrames* frames, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->brush_properties->setTool(tool);
    ui->sprite_canvas->setTool(tool);
    ui->frames_viewer->setAnimFrames(frames);
    ui->sprite_canvas->setAnimFrames(frames);


    connect(ui->brush_properties,
            &BrushProperties::showAirBrushIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showAirBrushIcon);

    connect(ui->brush_properties,
            &BrushProperties::showFillIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showFillIcon);

    connect(ui->brush_properties,
            &BrushProperties::showEraseIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showEraseIcon);

    connect(ui->brush_properties,
            &BrushProperties::showBrushIcon,
            ui->sprite_canvas,
            &SpriteCanvas::showBrushIcon);

    connect(ui->actionHelp,
            &QAction::triggered,
            this,
            &MainWindow::HelpTriggered);

    connect(ui->actionOpen,
            &QAction::triggered,
            this,
            &MainWindow::OpenTriggered);

    connect(ui->actionNew,
            &QAction::triggered,
            frames,
            &AnimationFrames::deleteAllFrames);


    connect(ui->actionClear,
            &QAction::triggered,
            frames,
            &AnimationFrames::clearSelectedFrame);

    connect(ui->sprite_canvas,
            &SpriteCanvas::frameDrawnOn,
            ui->frames_viewer,
            &FramesViewer::onFrameDrawnOn);


    connect(ui->actionNew,
            &QAction::triggered,
            frames,
            &AnimationFrames::deleteAllFrames);

    connect(frames,
            &AnimationFrames::deleteEveryFrame,
            ui->frames_viewer,
            &FramesViewer::deleteAllFrames);

    connect(frames,
            &AnimationFrames::frameCleared,
            ui->sprite_canvas,
            &SpriteCanvas::onExternalFrameUpdate);

    connect(frames,
            &AnimationFrames::frameCleared,
            ui->frames_viewer,
            &FramesViewer::onFrameDrawnOn);

    connect(frames,
            &AnimationFrames::framesLoadedFromFile,
            ui->sprite_canvas,
            &SpriteCanvas::onExternalFrameUpdate);

    connect(frames,
            &AnimationFrames::framesLoadedFromFile,
            ui->frames_viewer,
            &FramesViewer::onFrameDrawnOn);

    connect(frames,
            &AnimationFrames::frameAdded,
            ui->sprite_canvas,
            &SpriteCanvas::onExternalFrameUpdate);

    connect(frames,
            &AnimationFrames::animationIndexChanged,
            ui->sprite_canvas,
            &SpriteCanvas::onExternalFrameUpdate);

    connect(ui->frames_viewer,
            &FramesViewer::updateSprite,
            ui->sprite_canvas,
            &SpriteCanvas::updateSprite);

    connect(frames,
            &AnimationFrames::fileLoadError,
            this,
            &MainWindow::loadFileError);

    connect(frames,
            &AnimationFrames::fileSaveError,
            this,
            &MainWindow::saveFileError);


    connect(this,
            &MainWindow::openClicked,
            frames,
            &AnimationFrames::loadFromFile);

    connect(ui->actionSave_As,
            &QAction::triggered,
            this,
            &MainWindow::saveAsTriggered);

    connect(this,
            &MainWindow::saveAsClicked,
            frames,
            &AnimationFrames::saveToFile);

    connect(frames,
            &AnimationFrames::filePathChanged,
            ui->fileNameLabel,
            &QLabel::setText);

    connect(frames,
            &AnimationFrames::disableMenuBar,
            ui->menuFile,
            &QMenuBar::setDisabled);

    connect(frames,
            &AnimationFrames::enableMenuBar,
            ui->menuFile,
            &QMenuBar::setEnabled);

    connect(frames,
            &AnimationFrames::disableMenuBar,
            ui->menuEdit,
            &QMenuBar::setDisabled);

    connect(frames,
            &AnimationFrames::enableMenuBar,
            ui->menuEdit,
            &QMenuBar::setEnabled);

    connect(ui->actionSave,
            &QAction::triggered,
            this,
            &MainWindow::saveTriggered);

    connect(this,
            &MainWindow::saveClicked,
            frames,
            &AnimationFrames::saveToFile);

}

/// @brief Destructor for MainWindow.
MainWindow::~MainWindow()
{
    delete ui;
}

/// @brief When help is clicked, this method is called through the connection.
/// Displays a message box with help information.
void MainWindow::HelpTriggered()
{
    QMessageBox::information(this, "About", "help");
}

/// @brief When open is clicked, this method is called through the connection.
/// Allows the user to open a sprite editor project.
void MainWindow::OpenTriggered()
{
    QString fileContent;
    QString filename= QFileDialog::getOpenFileName(this, "Choose File");
    emit openClicked(filename);
}

/// @brief When open is clicked, this method is called through the connection.
/// Allows the user to open a sprite editor project.
void MainWindow::saveAsTriggered()
{
    QString fileContent;
    QString filename= QFileDialog::getSaveFileName();
    emit saveAsClicked(filename);
}

void MainWindow::saveTriggered(){
    QString filename = ui->fileNameLabel->text();
    QStringList arr = filename.split("Current File: ");
    filename = arr[1];
    emit saveClicked(filename);
}
void MainWindow::saveFileError(){
    QMessageBox::information(this, "Error saving file", "File type may be incorrect.");
}

void MainWindow::loadFileError(){
    QMessageBox::information(this, "Error opening file", "File may not have enough elements or type may be incorrect");
}
