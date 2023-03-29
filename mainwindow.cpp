#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brushproperties.h"


MainWindow::MainWindow(Tool* tool, AnimationFrames* frames, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->brush_properties->setTool(tool);
    ui->sprite_canvas->setTool(tool);
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
    //    connect(ui->actionAbout,
    //            &QMenuBar::triggered,
    //            this,
    //            &MainWindow::OnActionAboutTriggered)

}


MainWindow::~MainWindow()
{
    delete ui;
}

//will change name
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "help");
}

//will change name
void MainWindow::on_actionOpen_triggered()
{
    QString fileContent;

    QString filename= QFileDialog::getOpenFileName(this, "Choose File");


    if(filename.isEmpty())
        return;

    QFile file(filename);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);

    fileContent= in.readAll();

    file.close();

}

