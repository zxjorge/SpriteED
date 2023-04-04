#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brushproperties.h"

/*
 * NajMingle: 
 * CS3505
 * A7: Sprite Editor
 * 
 */

/// @brief 
/// @param tool 
/// @param frames 
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

    connect(ui->actionClear,
            &QAction::triggered,
            frames,
            &AnimationFrames::clearSelectedFrame);

    connect(ui->sprite_canvas,
            &SpriteCanvas::frameDrawnOn,
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
}

/// @brief 
MainWindow::~MainWindow()
{
    delete ui;
}

/// @brief 
void MainWindow::HelpTriggered()
{
    QMessageBox::information(this, "About", "help");
}

/// @brief 
void MainWindow::OpenTriggered()
{
    QString fileContent;
    QString filename= QFileDialog::getOpenFileName(this, "Choose File");

    if(filename.isEmpty())
        return;

    QFile file(filename);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);
    fileContent = in.readAll();
    file.close();
}

