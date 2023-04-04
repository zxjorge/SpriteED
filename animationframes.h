#ifndef ANIMATIONFRAMES_H
#define ANIMATIONFRAMES_H
#include <QObject>
#include <vector>
#include <QImage>
#include <QTimer>

using std::vector, std::string;

class AnimationFrames: public QObject
{
    Q_OBJECT

public:
    explicit AnimationFrames(QObject *parent = nullptr);
    QImage addFrame();
    QImage getSelectedFrame();
    void updateSelectedFrame(QImage image);
    void deleteFrame(int index);
    int getFrameCount();
    void clear();
    void setSelectedIndex(int index);
    int getSelectedIndex();
    void removeFrame(int id);
    void setFPS(int newFPS);
    void startAnimation();
    void stopAnimation();
    bool isAnimating();

signals:
    void frameAdded();
    void animationIndexChanged();
    void frameCleared();

public slots:
     void clearSelectedFrame();

private slots:
    void saveToFile(QString filename);
    void loadFromFile(QString filename);

private:
    vector<QImage> frames;
    int width;
    int height;
    int selectedIndex;
    int fps;
    QTimer animTimer;
};

#endif // ANIMATIONFRAMES_H
