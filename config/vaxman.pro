# Edited by :  Melwyn Francis Carlo (2021)


QT += core gui    \
      multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


DESTDIR  = ../bin
TARGET   = vaxman
TEMPLATE = app


DEFINES     += QT_DEPRECATED_WARNINGS

# DEFINES   += QT_DISABLE_DEPRECATED_BEFORE=0x060000


INCLUDEPATH += ../headers

SOURCES     += ../src/vaxman.cpp    \
               ../src/blinky.cpp    \
               ../src/pinky.cpp     \
               ../src/ghost.cpp     \
               ../src/clyde.cpp     \
               ../src/inky.cpp      \
               ../src/main.cpp      \
               ../src/app.cpp

HEADERS     += ../headers/vaxman.h  \
               ../headers/blinky.h  \
               ../headers/pinky.h   \
               ../headers/ghost.h   \
               ../headers/clyde.h   \
               ../headers/inky.h    \
               ../headers/app.h

RESOURCES   += qrc.qrc

