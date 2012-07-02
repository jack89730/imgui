######################################################################
# Automatically generated by qmake (2.01a) ?? 7? 1 13:25:39 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+=debug
# Input
HEADERS += generaloption.h \
           imgfiledlg.h \
           imgfilemodel.h \
           loadformats.h \
           mainwindow.h \
           resizegrp.h
SOURCES += generaloption.cpp \
           imgfiledlg.cpp \
           imgfilemodel.cpp \
           loadformats.cpp \
           main.cpp \
           mainwindow.cpp \
           resizegrp.cpp

INCLUDEPATH +=  /usr/include/GraphicsMagick
CXXFLAGS += -Wall -g -fno-strict-aliasing -fPIE -fstack-protector --param ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -O2 -pthread
LDFLAGS +=  -L/usr/lib -fPIE -pie -Wl,-z,relro -Wl,-z,now -L/usr/lib/X11 -L/usr/lib -L/usr/lib
if (exists(/usr/lib64)) {
  LIBS += -L/usr/lib64 -lGraphicsMagick++ -lGraphicsMagick -llcms -ltiff -lfreetype -ljasper -ljpeg -lpng -lwmflite -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lgomp -lpthread -lltdl
}
 else {
  LIBS += -L/usr/lib -lGraphicsMagick++ -lGraphicsMagick -llcms -ltiff -lfreetype -ljasper -ljpeg -lpng -lwmflite -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lgomp -lpthread -lltdl
 }

