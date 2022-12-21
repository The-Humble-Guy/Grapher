QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./include ./include/lib
VPATH += ./src ./src/lib

SOURCES += \
    function.cpp \
    main.cpp \
    mainwidget.cpp \
    src/expression.cpp \
    src/lexisChecker.cpp \
    src/lib/qcustomplot.cpp \
    src/syntax_checker.cpp \
    src/token.cpp \
    src/token_manager.cpp \
    src/value.cpp

HEADERS += \
    function.h \
    include/definitions.h \
    include/expression.h \
    include/lexisChecker.h \
    include/lib/qcustomplot.h \
    include/syntax_checker.h \
    include/token.h \
    include/token_manager.h \
    include/value.h \
    mainwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
