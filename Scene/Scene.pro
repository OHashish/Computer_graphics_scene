TEMPLATE = app
TARGET = Scene
INCLUDEPATH += . /opt/local/include

QT += widgets opengl gui 

windows: { LIBS += -lOpenGL32 -lGLU32 }
!windows: { LIBS += -lGLU }

# Input
HEADERS += \
    SceneWidget.h \
    SceneWindow.h
SOURCES += \
           SceneMain.cpp \
           SceneWidget.cpp \
           SceneWindow.cpp
