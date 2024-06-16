QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    creditwindow.cpp \
    graphwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    s21_calc.c \
    s21_credit.c

HEADERS += \
    creditwindow.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h \
    s21_calc.h \
    s21_credit.h

FORMS += \
    creditwindow.ui \
    graphwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
