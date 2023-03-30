#ifndef ANIMATIONFRAMES_H
#define ANIMATIONFRAMES_H
#include "QtWidgets/qwidget.h"
#include <QObject>
#include <vector>
#include <QImage>

using std::vector, std::string;

class AnimationFrames:public QWidget
{
public:
    explicit AnimationFrames(QWidget *parent = nullptr);
    QImage addFrame();
    QImage getSelectedFrame();
    void updateSelectedFrame(QImage image);
    void deleteFrame(int index);
    int getFrameCount();
    void clear();
    void setSelectedIndex(int index);
    int getSelectedIndex();

private slots:
    void saveToFile(QString filename);
    void loadFromFile(QString filename);

private:
    vector<QImage> frames;
    int width;
    int height;
    int selectedIndex;

public slots:
     void clearSelectedFrame();
};

#endif // ANIMATIONFRAMES_H
