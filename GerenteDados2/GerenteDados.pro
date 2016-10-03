#-------------------------------------------------
#
# Project created by QtCreator 2011-06-23T18:01:48
#
#-------------------------------------------------

QT       += core gui network opengl

TARGET = GerenteDados
TEMPLATE = app

INCLUDEPATH +=  ../ProtoLIB
LIBS += -L../ProtoLIB -lproto

INCLUDEPATH += Comunicacao \
               GerenteVisao \
               GerenteEstado

SOURCES +=  main.cpp\
            GerenteVisao/robo.cpp \
            GerenteVisao/gerenteVisao.cpp \
            GerenteVisao/bola.cpp \
            GerenteEstado/gerenteEstado.cpp \
            mainwindow.cpp \
            visualizacao.cpp \
    config.cpp

HEADERS  += GerenteVisao/robo.h \
            GerenteVisao/gerenteVisao.h \
            GerenteVisao/bola.h \
            GerenteEstado/gerenteEstado.h \
            mainwindow.h \
            visualizacao.h \
            definitions.h \
    config.h

OTHER_FILES += config/config.ini

QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -O3 -frounding-math


LIBS    += -lglut -lGLU -lprotobuf  `pkg-config --libs --cflags opencv`  -lCGAL

FORMS += \
    mainwindow.ui
