QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCheckers
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    checkerspicture.cpp \
    checkersstate.cpp \
    checkersgame.cpp \
    settingsdialog.cpp \
HEADERS += \
    checkersgame.cpp \
    checkerspicture.cpp \
    checkersstate.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    checkersgame.cpp \
    checkerspicture.cpp \
    checkersstate.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp
FORMS += \
    mainwindow.ui \
    settingsdialog.ui
RESOURCES += icons.qrc
OTHER_FILES +=

HEADERS += \
    checkersgame.h \
    checkerspicture.h \
    checkersstate.h \
    mainwindow.h \
    settingsdialog.h
