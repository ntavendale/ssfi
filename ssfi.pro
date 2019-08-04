TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pthread

SOURCES += main.cpp \
    utilities.cpp \
    fileprocessor.cpp \
    wordmap.cpp \
    threadidlist.cpp

HEADERS += \
    utilities.h \
    fileprocessor.h \
    wordmap.h \
    threadidlist.h

LIBS += -pthread
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_filesystem

