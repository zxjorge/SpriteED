/**
 * animationframes.h made by NajMingle for A7: Sprite Editor Implementation - CS 3505 Spring 2023
 * Model for handling frames of an animation
 * Reviewed by: Najman Husaini
 */
#include "animationframes.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QFileInfo>
#include <iostream>

/**
 * @brief AnimationFrames::AnimationFrames Constructor for AnimationFrames. Sets up for frame animating.
 * @param parent widget that is used to help handle memory and resources.
 */
AnimationFrames::AnimationFrames(QObject *parent) :
    QObject(parent),
    frames(vector<QImage>()),
    width(32),
    height(32),
    selectedIndex(0),
    animTimer(QTimer(this))
{
    setFPS(1);
    animTimer.setTimerType(Qt::PreciseTimer);

    // Connection used for switching between the frames based on the frame speed.
    connect(&animTimer,
            &QTimer::timeout,
            this,
            [this] {
                selectedIndex++;
                if (selectedIndex >= (int)frames.size()) {
                    selectedIndex = 0;
                }
                emit animationIndexChanged();
                this->animTimer.start();
            });
}

/**
 * @brief AnimationFrames::addFrame Adds a new frame that can be edited
 * @return The image representing the frame
 */
QImage AnimationFrames::addFrame()
{
    selectedIndex = frames.size();
    QImage img = QImage(width, height, QImage::Format_ARGB32);
    img.fill(QColor(0, 0, 0, 0));
    frames.push_back(img);
    emit frameAdded();
    return img;
}


/**
 * @brief AnimationFrames::getSelectedFrame returns the currently selected frame.
 * @return the currently selected frame as a QImage.
 */
QImage AnimationFrames::getSelectedFrame()
{
    return frames.at(selectedIndex);
}


/**
 * @brief AnimationFrames::deleteFrame deletes a frame selected by the user.
 * @param index Used to specify which frame is to be deleted.
 */
void AnimationFrames::deleteFrame(int index)
{
    frames.erase(frames.begin() + index);
    if (frames.empty()) {
        addFrame();
    }
}

/**
 * @brief AnimationFrames::deleteAllFrames Deletes all the frames
 */
void AnimationFrames::deleteAllFrames()
{
    for(int i = 0; i < (int)frames.size(); i++){
        setSelectedIndex(i);
        clearSelectedFrame();
    }
    setSelectedIndex(0);
    emit deleteEveryFrame(frames.size());
    emit filePathChanged("Current File: ");
}


/**
 * @brief AnimationFrames::getFrameCount Returns the total number of frames present on the sprite editor.
 * @return number of frames
 */
int AnimationFrames::getFrameCount()
{
    return frames.size();
}


/**
 * @brief AnimationFrames::clear Deletes all the frames, adds a new frame to ensure at least one frame at all times.
 */
void AnimationFrames::clear() {
    frames.clear();
    addFrame();
}


/**
 * @brief AnimationFrames::updateSelectedFrame updates the selected frame.
 * @param image The image to replace the outdated image in the frames list.
 */
void AnimationFrames::updateSelectedFrame(QImage image) {
    // Replace image at selectedIndex
    frames.at(selectedIndex) = image;
    wasModified = true;
}


/**
 * @brief AnimationFrames::saveToFile saves a sprite editor project to a file in JSON format.
 * @param filename The name of the file that will be saved to.
 */
void AnimationFrames::saveToFile(QString filename) {
    if (!filename.endsWith(".ssp")) {
        filename += ".ssp";
    }
    QJsonObject json = QJsonObject();

    // Sets all necessary JSON attributes to represent the current state of a sprite editor project.
    json["height"] = height;
    json["width"] = width;
    json["numberOfFrames"] = (long long int)frames.size();

    QJsonObject framesJson = QJsonObject();

    // Creates a JsonArray to represent a Json attribute that holds all the pixels and their colors.
    for (int i = 0; i < (int)frames.size(); i++) {
        QImage& frame = frames.at(i);
        QJsonArray frameJson = QJsonArray();
        for (int y = 0; y < height; y++) {
            QJsonArray row = QJsonArray();
            for (int x = 0; x < width; x++) {
                QJsonArray pixel = QJsonArray();
                QColor color = frame.pixelColor(x, y);
                pixel.append(color.red());
                pixel.append(color.green());
                pixel.append(color.blue());
                pixel.append(color.alpha());
                row.append(pixel);
            }
            frameJson.append(row);
        }
        framesJson["frame" + QString::number(i)] = frameJson;
    }

    json["frames"] = framesJson;

    // Writes to file.
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file );
        stream << QJsonDocument(json).toJson(QJsonDocument::Compact) << Qt::endl;
        QFileInfo fileInfo(filename);
        QString fname(fileInfo.fileName());
        wasModified = false;
        emit filePathChanged("Current File: " + fname);
    }
}


/**
 * @brief AnimationFrames::loadFromFile Loads a sprite editor project from a file
 * @param filename The file to be loaded from.
 */
void AnimationFrames::loadFromFile(QString filename) {

    // Reads from file.
    QFile file(filename);
    QJsonObject json;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream( &file );
        json = QJsonDocument::fromJson(stream.readAll().toLocal8Bit()).object();
        if(json.count()!=4 || !json.keys().contains("width") || !json.keys().contains("height") || !json.keys().contains("numberOfFrames")){
            emit fileLoadError();
        }
        else{
            // Parsing all the Json elements and updating the necessary objects.
            width = json["width"].toInt(32);
            height = json["height"].toInt(32);
            generateBackground();
            frames = vector<QImage>(json["numberOfFrames"].toInt(1));
            QJsonObject framesJson = json["frames"].toObject();

            for (QString& key : framesJson.keys()) {
                QImage image = QImage(width, height, QImage::Format_ARGB32);
                QJsonArray imageJson = framesJson[key].toArray();

                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        QJsonArray pixel = imageJson[y][x].toArray();
                        image.setPixelColor(
                            x,
                            y,
                            QColor(
                                pixel.at(0).toInt(),
                                pixel.at(1).toInt(),
                                pixel.at(2).toInt(),
                                pixel.at(3).toInt()
                                )
                            );
                    }
                }

                int index = key.right(1).toInt();
                frames.at(index) = image;
            }

            wasModified = false;
            emit framesLoadedFromFile();
            QFileInfo fileInfo(filename);
            QString fname(fileInfo.fileName());
            emit filePathChanged("Current File: " + fname);
        }
    }
}


/**
 * @brief AnimationFrames::setSelectedIndex Sets the selected frame's index.
 * @param index The index of the frame to be selected.
 */
void AnimationFrames::setSelectedIndex(int index){
    this->selectedIndex = index;
}


/**
 * @brief AnimationFrames::getSelectedIndex Get the selected frame's index
 * @return The index of the selected frame.
 */
int AnimationFrames::getSelectedIndex(){
    return selectedIndex;
}


/**
 * @brief AnimationFrames::clearSelectedFrame Public slot used to clear a single frame of any edits
 */
void AnimationFrames::clearSelectedFrame() {

    // Cannot be cleared if animation is running.
    if(!animTimer.isActive())
        frames.at(selectedIndex).fill(QColor(0, 0, 0, 0));
    emit frameCleared();
}


/**
 * @brief AnimationFrames::removeFrame Removes a frame.
 * @param id Uses id to determine the frame to be removed.
 */
void AnimationFrames::removeFrame(int id){
    frames.erase(frames.begin() + id);
}


/**
 * @brief AnimationFrames::setFPS Sets the frames per second for the animation.
 * @param newFPS The desired frames per second speed.
 */
void AnimationFrames::setFPS(int newFPS) {
    fps = newFPS;
    animTimer.setInterval(1000 / fps);
}


/**
 * @brief AnimationFrames::startAnimation Starts the animation timer.
 */
void AnimationFrames::startAnimation() {
    animTimer.start();
    emit disableMenuBar(true);
}


/**
 * @brief AnimationFrames::stopAnimation Stops the animation timer and enables the menu bar.
 */
void AnimationFrames::stopAnimation() {
    animTimer.stop();
    emit enableMenuBar(true);
}

/**
 * @brief AnimationFrames::isAnimating Checks if the animation is running.
 * @return true if animation is running and false otherwise.
 */
bool AnimationFrames::isAnimating() {
    return animTimer.isActive();
}


/**
 * @brief AnimationFrames::generateBackground Generates a background to be drawn behind the canvas.
 */
void AnimationFrames::generateBackground() {
    background = QImage(width, height, QImage::Format_Grayscale8);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x % 2 == y % 2) {
                background.setPixelColor(x, y, QColor(235, 235, 235));
            } else {
                background.setPixelColor(x, y, Qt::white);
            }
        }
    }
}

/**
 * @brief AnimationFrames::getBackground Retrieves a const binding to the background
 * @return
 */
const QImage& AnimationFrames::getBackground() {
    return background;
}

/**
 * @brief AnimationFrames::getWasModified Checks if any frame was modified without being saved
 * @return True iff a frame was modified and not saved
 */
bool AnimationFrames::getWasModified() {
    return wasModified;
}
