QT += core gui widgets sql network

TARGET = sqlite-thread
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp \
    DatabaseAccessor.cpp

HEADERS += main.hpp \
    MainWidget.hpp \
    DatabaseAccessor.hpp

FORMS += MainWidget.ui
