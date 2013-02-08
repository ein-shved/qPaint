# -------------------------------------------------
# Project created by QtCreator 2012-09-19T19:31:54
# -------------------------------------------------
TARGET = qPaint
TEMPLATE = app
SOURCES += src/GUI/gui.cpp \
    src/GUI/ImageScene.cpp \
    src/GUI/Validators.cpp \
    src/ArgParser/arg_parser.cpp \
    src/main.cpp \
    src/Engine/Filter.cpp \
    src/Engine/Engine.cpp \
    src/Engine/Callback.cpp \
    src/Engine/Filters/Hystogram.cpp \
    src/Engine/Filters/GreyWorld.cpp \
    src/Engine/Filters/Convolution.cpp \
    src/Engine/Filters/Sobel.cpp \
    src/Engine/Filters/Interpolation.cpp \
    src/Engine/Filters/Manually.cpp \
    src/Engine/Filters/Supplementary.cpp \
    src/Engine/Filters/GaussianS.cpp
HEADERS += src/GUI/gui.h \
    src/GUI/ImageScene.h \
    src/GUI/Validators.h \
    src/ArgParser/arg_parser.h \
    src/Engine/Filter.h \
    src/Engine/Engine.h \
    src/Engine/Callback.h \
    src/Engine/Filters/Hystogram.h \
    src/Engine/Filters/GreyWorld.h \
    src/Engine/Filters/Convolution.h \
    src/Engine/Filters/Sobel.h \
    src/Engine/Filters/Interpolation.h \
    src/Engine/Filters/Manually.h \
    src/Engine/Filters/Supplementary.h \
    src/Engine/Filters/GaussianS.h
FORMS += src/GUI/gui.ui \
	 src/GUI/Manually.ui

#uncomment for debug mode
#CONFIG+=debug

#use separable gaussian filter instead normal
#comment to use normal gaussian
DEFINES+=Use_Separable_Gauss

#use one of follow
#all callback methods in filters will be virtual
DEFINES+=Virtual_Callback
#callback methods in filers will be inline
#DEFINES+=Inline_Callback

#LIBS += -lboost_thread-mt -lboost_thread