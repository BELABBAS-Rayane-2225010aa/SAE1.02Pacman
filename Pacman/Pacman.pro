TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Fichier_jeu/game.cpp \
        Fichier_jeu/gridmanager.cpp\
        Fichier_jeu/params.cpp\
        main.cpp

        
include (mingl/mingl.pri)

HEADERS += \
    Fichier_jeu/game.h \
    Fichier_jeu/type.h \
    Fichier_jeu/gridmanager.h \
    Fichier_jeu/params.h


DISTFILES += \
    Nos_fichiers/Tuto \
    Nos_fichiers/Map1 \
    Nos_fichiers/config.yaml
