# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./src/widgets
# Target is a library:  

HEADERS += glowbutton.h \
           blinkbutton.h \
           timedisplay.h \
           vumeter.h \
           playlist.h \
           playlistviewitem.h \
           songlistview.h \
           timer.h
SOURCES += glowbutton.cpp \
           blinkbutton.cpp \
           timedisplay.cpp \
           vumeter.cpp \
           playlist.cpp \
           playlistviewitem.cpp \
           songlistview.cpp \
           timer.cpp
CONFIG += warn_on \
qt \
staticlib
TEMPLATE = lib
include(../../conf.pri)
FORMS += timerSettings.ui

#The following line was inserted by qt3to4
QT += xml  qt3support 

DESTDIR = .

INCLUDEPATH += ../../src

