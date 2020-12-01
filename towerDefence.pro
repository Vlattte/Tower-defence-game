QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arrow.cpp \
    ArrowTower.cpp \
    Base.cpp \
    Biggoblin.cpp \
    Chat.cpp \
    Enemy.cpp \
    Fireball.cpp \
    Freballtower.cpp \
    Goblin.cpp \
    Health.cpp \
    Stonebullet.cpp \
    Stonetower.cpp \
    Tower.cpp \
    Towerbuilder.cpp \
    Towerupgrade.cpp \
    UpdateHelper.cpp \
    game.cpp \
    gold.cpp \
    main.cpp \
    mainwindow.cpp \
    mapinfo.cpp \
    towerchoice.cpp

HEADERS += \
    Arrow.h \
    ArrowTower.h \
    Base.h \
    Biggoblin.h \
    Chat.h \
    Enemy.h \
    EnemyPoints.h \
    Fireball.h \
    Fireballtower.h \
    Goblin.h \
    Health.h \
    Stonebullet.h \
    Stonetower.h \
    Tower.h \
    Towerbuilder.h \
    Towerupgrade.h \
    UpdateHelper.h \
    Upgrades.h \
    game.h \
    gold.h \
    mainwindow.h \
    mapinfo.h \
    towerchoice.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    towerBuilder.png

FORMS += \
    mainwindow.ui \
    towerchoice.ui \
    towerupgrade.ui
