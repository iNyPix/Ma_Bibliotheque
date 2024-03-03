QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    addbookdialog.cpp \
    ressources/classes/addgooglebookdialog.cpp \
    ressources/classes/author.cpp \
    ressources/classes/book.cpp \
    ressources/classes/collection.cpp \
    ressources/classes/editor.cpp \
    ressources/classes/gender.cpp \
    main.cpp \
    bibliotheque.cpp \
    ressources/classes/querysql.cpp

HEADERS += \
    aboutdialog.h \
    addbookdialog.h \
    ressources/classes/addgooglebookdialog.h \
    ressources/classes/author.h \
    bibliotheque.h \
    ressources/classes/book.h \
    ressources/classes/collection.h \
    ressources/classes/editor.h \
    ressources/classes/gender.h \
    ressources/classes/querysql.h

FORMS += \
    aboutdialog.ui \
    addbookdialog.ui \
    bibliotheque.ui \
    ressources/classes/addgooglebookdialog.ui

TRANSLATIONS += \
    ressources/translations/MaBibliotheque_en_GB.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

