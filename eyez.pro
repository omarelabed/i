#-------------------------------------------------
#
# Project created by QtCreator 2013-12-09T17:27:45
#
#-------------------------------------------------

HEADERS += ./Base.h \
    ./CCanvas.h \
    ./ColorDef.h \
    ./Point2.h \
    ./Point3.h \
    ./GLRender.h \
    ./Sphere.h

#Source files
SOURCES += ./main.cpp \
    ./CCanvas.cpp \
    ./GLRender.cpp \
    ./Sphere.cpp

#Forms
FORMS += ./GLRender.ui

CONFIG += release
CONFIG += console

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
#INCLUDEPATH += /usr/local/include
INCLUDEPATH += "/opt/local/include/"
LIBS += "/opt/local/lib/libopencv*.dylib"
#LIBS += "/usr/local/lib/libopencv*.dylib"
#QT += core gui xml opengl
QT += opengl

OBJECTS_DIR = build
MOC_DIR = mocs
UI_DIR = uis

# Input
#include(GLRender.pri)

mac: LIBS += -framework GLUT
else:unix|win32: LIBS += -lGLUT

#QT       += core
#QT       -= gui

TARGET = eyez
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app

#unix|win32: LIBS += -lopencv_calib3d
#unix|win32: LIBS += -lopencv_stitching
#unix|win32: LIBS += -lopencv_calib3d
#unix|win32: LIBS += -lopencv_contrib
#unix|win32: LIBS += -lopencv_core
#unix|win32: LIBS += -lopencv_features2d
#unix|win32: LIBS += -lopencv_flann
#unix|win32: LIBS += -lopencv_gpu
#unix|win32: LIBS += -lopencv_highgui
#unix|win32: LIBS += -lopencv_imgproc
#unix|win32: LIBS += -lopencv_legacy
#unix|win32: LIBS += -lopencv_ml
#unix|win32: LIBS += -lopencv_nonfree
#unix|win32: LIBS += -lopencv_objdetect
#unix|win32: LIBS += -lopencv_photo
#unix|win32: LIBS += -lopencv_stitching
#unix|win32: LIBS += -lopencv_superres
#unix|win32: LIBS += -lopencv_video
#unix|win32: LIBS += -lopencv_videostab
