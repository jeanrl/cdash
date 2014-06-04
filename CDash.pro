#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T11:17:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = CDash
TEMPLATE = app

TRANSLATIONS = languages/CDash_en.ts \
               languages/CDash_es.ts

LIBS += -L/usr/lib64 -lX11 -lXdamage

SOURCES += main.cpp\
        cdash.cpp \
    relogio/wrelogio.cpp \
    configdash.cpp \
    cronometro/widget.cpp \
    cronometro/jcronometro.cpp \
    cronometro/configcron.cpp

HEADERS  += cdash.h \
    relogio/wrelogio.h \
    configdash.h \
    cronometro/widget.h \
    cronometro/jcronometro.h \
    cronometro/configcron.h

RESOURCES += \
    relogio/rscRelogio.qrc \
    rcCDash.qrc \
    cronometro.qrc

FORMS += \
    configdash.ui \
    cronometro/widget.ui \
    cronometro/configcron.ui

