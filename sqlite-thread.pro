QT += core gui widgets sql network

TARGET = sqlite-thread
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp

HEADERS += main.hpp \
    MainWidget.hpp

FORMS += MainWidget.ui
