TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    utilities.cpp \
    fileprocessor.cpp \
    wordmap.cpp

HEADERS += \
    utilities.h \
    fileprocessor.h \
    wordmap.h

LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_filesystem
