#include "animationframes.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>

/// @brief 
/// @param parent 
AnimationFrames::AnimationFrames(QObject *parent) :
    QObject(parent),
    frames(vector<QImage>()),
    width(192),
    height(128),
    selectedIndex(0)
{
}

/// @brief 
/// @return 
QImage AnimationFrames::addFrame()
{
    selectedIndex = frames.size();
    QImage img = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    frames.push_back(img);
    emit frameAdded();
    return img;
}

/// @brief 
/// @return 
QImage AnimationFrames::getSelectedFrame()
{
    return frames.at(selectedIndex);
}

/// @brief 
/// @param index 
void AnimationFrames::deleteFrame(int index)
{
    frames.erase(frames.begin() + index);
    if (frames.empty()) {
        addFrame();
    }
}

/// @brief 
/// @return 
int AnimationFrames::getFrameCount()
{
    return frames.size();
}

/// @brief 
void AnimationFrames::clear() {
    frames.clear();
    addFrame();
}

/// @brief 
/// @param image 
void AnimationFrames::updateSelectedFrame(QImage image) {
    // Replace image at selectedIndex
    frames.at(selectedIndex) = image;
}

void AnimationFrames::saveToFile(QString filename) {
    QJsonObject json = QJsonObject();
    json["height"] = height;
    json["width"] = width;
    json["numberOfFrames"] = (long long int)frames.size();

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
        json[&"json" [ i]] = frameJson;
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file );
        stream << QJsonDocument(json).toJson(QJsonDocument::Compact) << Qt::endl;
    }
    else {
        // Error Message
    }
}

void AnimationFrames::loadFromFile(QString filename) {
    QFile file(filename);
    QJsonObject json;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream( &file );
        json = QJsonDocument::fromJson(stream.readAll().toLocal8Bit()).object();
    }
    else {
        // Error Message
        return;
    }

    width = json["width"].toInt(32);
    height = json["height"].toInt(32);
    frames = vector<QImage>(json["numberOfFrames"].toInt(1));

    for (QString& key : json.keys()) {
        if (!key.startsWith("frame")) {
            continue;
        }
        QImage image = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
        QJsonArray imageJson = json[key].toArray();
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

        int index = key.right(5).toInt();
        frames.at(index) = image;
    }
}

/// @brief 
/// @param index 
void AnimationFrames::setSelectedIndex(int index){
    this->selectedIndex = index;
}

/// @brief 
/// @return 
int AnimationFrames::getSelectedIndex(){
    return selectedIndex;
}

/// @brief 
void AnimationFrames::clearSelectedFrame() {
    frames.at(selectedIndex).fill(Qt::white);
}
