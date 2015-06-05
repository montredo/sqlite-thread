QT += core gui widgets sql network

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

DESTDIR = build
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
