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
    this->frames = frames;

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

    heightSpinBox = new QSpinBox(&inputBox);
    widthSpinBox = new QSpinBox(&inputBox);

    heightSpinBox->setRange(1, 128);
    heightSpinBox->setValue(32);

    widthSpinBox->setRange(1, 128);
    widthSpinBox->setValue(32);

    heightLabel = new QLabel("Height", &inputBox);
    widthLabel = new QLabel("Width", &inputBox);
    okButton = new QPushButton("Ok", &inputBox);
    inputLabel = new QLabel("Please enter the height and width:", &inputBox);

    connect(okButton, &QPushButton::clicked, &inputBox, [=] {
        int height = heightSpinBox->value();
        int width = widthSpinBox->value();
        frames->setHeightWidth(height,width);
        inputBox.close();
    });

    connect(&inputBox, &QDialog::rejected, &inputBox, [=] {
        int height = heightSpinBox->value();
        int width = widthSpinBox->value();
        frames->setHeightWidth(height,width);
        inputBox.close();
    });


    inputLayout = new QVBoxLayout(&inputBox);
    inputLayout->addWidget(inputLabel);

    heightLayout = new QHBoxLayout();
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightSpinBox);
    inputLayout->addLayout(heightLayout);

    widthLayout = new QHBoxLayout();
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthSpinBox);
    inputLayout->addLayout(widthLayout);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    inputLayout->addLayout(buttonLayout);

    inputBox.exec();
}

/**
 * @brief MainWindow::~MainWindow
 * Destructor for MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::HelpTriggered
 * When help is clicked, this method is called through the connection.
 * Displays a message box with help information.
 */
void MainWindow::HelpTriggered()
{
    QMessageBox help;
    help.setDefaultButton(QMessageBox::Ok);
    QPixmap helpIcon = QPixmap(":/icons/annotatedUI.png").scaled(750, 750, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    help.setIconPixmap(helpIcon);
    help.show();
    help.exec();
}

/**
 * @brief MainWindow::OpenTriggered
 * When open is clicked, this method is called through the connection.
 * Allows the user to open a sprite editor project.
 */
void MainWindow::OpenTriggered()
{
    if(frames->getWasModified())
        saveAsTriggered();

    QString filename = QFileDialog::getOpenFileName(this, "Choose Project",
                                                    ".",
                                                    "Project (*.ssp)");
    if (filename.size() == 0) {
        return;
    }
    emit openClicked(filename);
}

/**
 * @brief MainWindow::saveAsTriggered
 * When open is clicked, this method is called through the connection.
 * Allows the user to open a sprite editor project.
 */
void MainWindow::saveAsTriggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Project",
                                                    "Sprite1",
                                                    "Project (*.ssp)");
    if (filename.size() == 0) {
        return;
    }
    emit saveAsClicked(filename);
}

/**
 * @brief MainWindow::saveTriggered
 * This saves the file for the user
 */
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

/**
 * @brief MainWindow::saveFileError
 * Prompts the user that there was error saving file
 */
void MainWindow::saveFileError(){
    QMessageBox::information(this, "Error saving file", "File type may be incorrect.");
}

/**
 * @brief MainWindow::loadFileError
 * Prompts the user that there was error loading file.
 */
void MainWindow::loadFileError(){
    QMessageBox::information(this, "Error opening file", "File may not have enough elements or type may be incorrect");
}
