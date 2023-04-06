/**
 * mainwindow.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * The main window of our application
 * Reviewed by: George Benyeogor
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brushproperties.h"
#include <QInputDialog>

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
            ui->frames_viewer,
            &FramesViewer::onProjectLoaded);

    connect(frames,
            &AnimationFrames::framesLoadedFromFile,
            ui->sprite_canvas,
            &SpriteCanvas::onExternalFrameUpdate);

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

    connect(ui->resized,
            &QCheckBox::toggled,
            ui->sprite_canvas,
            &SpriteCanvas::setResized);

    QDialog dialog(this);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QPushButton *okButton = new QPushButton("Ok", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    lineEdit->setPlaceholderText("Enter a value between 1 and 128");
    connect(okButton, &QPushButton::clicked, &dialog, [&] {
        storeValue(lineEdit->text());
        dialog.close();
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::close);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(lineEdit);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    dialog.exec();

}

void MainWindow::storeValue(QString value)
{
    m_value = value;
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
    QString filename = QFileDialog::getOpenFileName(this, "Choose Project",
                                                    ".",
                                                    "Project (*.ssp)");
    if (filename.size() == 0) {
        return;
    }
    emit openClicked(filename);
}

/// @brief When open is clicked, this method is called through the connection.
/// Allows the user to open a sprite editor project.
void MainWindow::saveAsTriggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Project",
                                                    ".",
                                                    "Project (*.ssp)");
    if (filename.size() == 0) {
        return;
    }
    emit saveAsClicked(filename);
}

void MainWindow::saveTriggered(){
    QString filename = ui->fileNameLabel->text();
    QStringList arr = filename.split("Current File: ");
    if (arr.size() == 1) {
        saveAsTriggered();
        return;
    }
    filename = arr[1];
    emit saveClicked(filename);
}
void MainWindow::saveFileError(){
    QMessageBox::information(this, "Error saving file", "File type may be incorrect.");
}

void MainWindow::loadFileError(){
    QMessageBox::information(this, "Error opening file", "File may not have enough elements or type may be incorrect");
}
