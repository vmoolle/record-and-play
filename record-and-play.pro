QT += quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    recordandplay.cpp \
    recorder.cpp \
    player.cpp

RESOURCES += qml.qrc

HEADERS += \
    recordandplay.h \
    iaudio.h \
    recorder.h \
    player.h
