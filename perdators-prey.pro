QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_classes/animal.cpp \
    base_classes/plant.cpp \
    field.cpp \
    main.cpp \
    mainwindow.cpp \
    species/animals/bunny.cpp \
    species/animals/deer.cpp \
    species/animals/fox.cpp \
    species/animals/wolf.cpp \
    species/plants/grass.cpp \
    species/plants/mushroom.cpp \
    statswindow.cpp \
    type/predator.cpp \
    type/prey.cpp

HEADERS += \
    base_classes/animal.h \
    base_classes/plant.h \
    field.h \
    mainwindow.h \
    species/animals/bunny.h \
    species/animals/deer.h \
    species/animals/fox.h \
    species/animals/wolf.h \
    species/plants/grass.h \
    species/plants/mushroom.h \
    statswindow.h \
    type/predator.h \
    type/prey.h

FORMS += \
    mainwindow.ui \
    statswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
