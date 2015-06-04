QT += core gui widgets sql network

TARGET = sqlite-thread
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp \
    DatabaseAccessor.cpp \
    DatabaseThread.cpp

HEADERS += main.hpp \
    MainWidget.hpp \
    DatabaseAccessor.hpp \
    DatabaseThread.hpp

FORMS += MainWidget.ui
