TEMPLATE = app
TARGET = weatherinfo

HEADERS = abstractstorage.h \
          dayview.h \
          mainwidget.h \
          staticstorage.h \
          tableview.h \
          temperatureview.h \
          weathermodel.h \
          weatherset.h \
          webstorage.h \
          worldview.h

SOURCES = dayview.cpp \
          main.cpp \
          mainwidget.cpp \
          staticstorage.cpp \
          tableview.cpp \
          temperatureview.cpp \
          weathermodel.cpp \
          weatherset.cpp \
          webstorage.cpp \
          worldview.cpp

RESOURCES = ../images/image.qrc

QT += xmlpatterns
