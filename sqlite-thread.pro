QT += core gui widgets sql network

TARGET = sqlite-thread
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp

HEADERS += MainWidget.hpp

FORMS += MainWidget.ui
