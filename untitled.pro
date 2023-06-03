QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#MATERIAL-SDK
LIBS += $$PWD/libs/libcomponents.a
INCLUDEPATH += $$PWD/libs/include

SOURCES += \
    adduserdialog.cpp \
    changeticketdialog.cpp \
    check.cpp \
    chgpddialog.cpp \
    dialog1.cpp \
    dialogaddticket.cpp \
    form.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    md5.cpp \
    messagebox1.cpp \
    opdialog.cpp \
    prompt1.cpp \
    psgdialog.cpp \
    regdialog.cpp \
    ticket.cpp \
    user.cpp \
    user_crl.cpp \
    widget.cpp \
    widget_user.cpp

HEADERS += \
    adduserdialog.h \
    changeticketdialog.h \
    chgpddialog.h \
    dialog1.h \
    dialogaddticket.h \
    form.h \
    logindialog.h \
    mainwindow.h \
    md5.h \
    messagebox1.h \
    opdialog.h \
    prompt1.h \
    psgdialog.h \
    regdialog.h \
    ticket.h \
    user.h \
    user_crl.h \
    widget.h \
    widget_user.h

FORMS += \
    adduserdialog.ui \
    changeticketdialog.ui \
    chgpddialog.ui \
    dialog1.ui \
    dialogaddticket.ui \
    form.ui \
    mainwindow.ui \
    messagebox1.ui \
    opdialog.ui \
    prompt1.ui \
    psgdialog.ui \
    regdialog.ui \
    widget.ui \
    widget_user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imag.qrc \
    imag.qrc \
    imag.qrc \
    res.qrc \
    res.qrc

DISTFILES += \
    Image/manager.png \
    Tomas.jpg \
    User_Data.dat \
    User_Ticket/321.txt \
    User_Ticket/54321.txt \
    User_Ticket/aaa.txt \
    User_Ticket/admin.txt \
    User_Ticket/cccc.txt \
    User_Ticket/libai.txt \
    User_Ticket/ppp.txt \
    User_Ticket/shabi.txt \
    User_Ticket/sm.txt \
    hchsk.txt \
    ticket.txt \
    user.txt