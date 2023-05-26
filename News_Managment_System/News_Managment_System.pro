QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcategory.cpp \
    addn.cpp \
    adminmainwindow.cpp \
    categorymainwindow.cpp \
    categoryvector.cpp \
    comments.cpp \
    deletecategory.cpp \
    findcategory.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    news.cpp \
    news_page.cpp \
    newsadminwindow.cpp \
    newslinkedlist.cpp \
    sign_up.cpp \
    updaten.cpp \
    user.cpp \
    usersdatabase.cpp

HEADERS += \
    Globals.h \
    addcategory.h \
    addn.h \
    adminmainwindow.h \
    categorymainwindow.h \
    categoryvector.h \
    comments.h \
    deletecategory.h \
    fileheader.h \
    findcategory.h \
    login.h \
    mainwindow.h \
    news.h \
    news_page.h \
    newsadminwindow.h \
    newslinkedlist.h \
    sign_up.h \
    updaten.h \
    user.h \
    usersdatabase.h

FORMS += \
    addcategory.ui \
    addn.ui \
    adminmainwindow.ui \
    categorymainwindow.ui \
    comments.ui \
    deletecategory.ui \
    findcategory.ui \
    login.ui \
    mainwindow.ui \
    news_page.ui \
    newsadminwindow.ui \
    sign_up.ui \
    updaten.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
