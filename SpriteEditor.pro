QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationframes.cpp \
    brush.cpp \
    brushproperties.cpp \
    framesviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    spritecanvas.cpp

HEADERS += \
    animationframes.h \
    brush.h \
    brushproperties.h \
    framesviewer.h \
    mainwindow.h \
    spritecanvas.h

FORMS += \
    brushproperties.ui \
    framesviewer.ui \
    mainwindow.ui \
    spritecanvas.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Resources.qrc
