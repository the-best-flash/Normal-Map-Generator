# -------------------------------------------------
# Project created by QtCreator 2010-04-08T15:36:36
# -------------------------------------------------
QT += opengl
TARGET = NormalMapGenerator
TEMPLATE = app
SOURCES += main.cpp \
    normalmaplist.cpp \
    nlist.cpp \
    generateselected.cpp \
    addlayer.cpp \
    normalmapsettings.cpp \
    normalfromimage.cpp \
    normalfromnormal.cpp \
    normalfromgenerator.cpp \
    normalfromquadimage.cpp \
    imageselect.cpp \
    previewwindow.cpp \
    nmap.cpp \
    nlayer.cpp \
    ImageProcessing/TextureMaster.cpp \
    ImageProcessing/My_Math.cpp \
    ImageProcessing/Misc_Func.cpp \
    ImageProcessing/HLSL_Func.cpp \
    LinkedList.cpp \
    heightlayer.cpp \
    imagelayer.cpp \
    normallayer.cpp \
    quadimagelayer.cpp \
    generatorlayer.cpp \
    image.cpp \
    pixel.cpp
HEADERS += normalmaplist.h \
    nlist.h \
    generateselected.h \
    addlayer.h \
    normalmapsettings.h \
    normalfromimage.h \
    normalfromnormal.h \
    normalfromgenerator.h \
    normalfromquadimage.h \
    imageselect.h \
    previewwindow.h \
    nmap.h \
    nlayer.h \
    ImageProcessing/TextureMaster.h \
    ImageProcessing/My_Math.h \
    ImageProcessing/Misc_Func.h \
    ImageProcessing/HLSL_Func.h \
    LinkedList.h \
    heightlayer.h \
    imagelayer.h \
    normallayer.h \
    quadimagelayer.h \
    generatorlayer.h \
    image.h \
    pixel.h
FORMS += normalmaplist.ui \
    generateselected.ui \
    addlayer.ui \
    normalmapsettings.ui \
    normalfromimage.ui \
    normalfromnormal.ui \
    normalfromgenerator.ui \
    normalfromquadimage.ui \
    imageselect.ui \
    previewwindow.ui
INCLUDEPATH += include/
INCLUDEPATH += inc/
QMAKE_CXXFLAGS += -fopenmp
QMAKE_APP_FLAG += -fopenmp
QMAKE_LFLAGS += -fopenmp
RESOURCES += Resources.qrc
LIBS += -L../NormalMapGenerator/lib/ -lDevIL
