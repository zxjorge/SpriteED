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
    const QImage& getBackground();

signals:
    void frameAdded();
    void animationIndexChanged();
    void frameCleared();
    void framesLoadedFromFile();
    void fileLoadError();
    void fileSaveError();
    void filePathChanged(QString);
    void disableMenuBar(bool);
    void enableMenuBar(bool);
    void deleteEveryFrame(int);

public slots:
     void clearSelectedFrame();
     void loadFromFile(QString filename);
     void saveToFile(QString filename);
     void deleteAllFrames();

private:
    vector<QImage> frames;
    int width;
    int height;
    int selectedIndex;
    int fps;
    QTimer animTimer;
    QImage background;

    void generateBackground();
};

#endif // ANIMATIONFRAMES_H
