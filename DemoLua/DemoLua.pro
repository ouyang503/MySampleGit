#-------------------------------------------------
#
# Project created by QtCreator 2018-09-04T09:25:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemoLua
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cprocess_lua.cpp

HEADERS  += mainwindow.h \
    cprocess_lua.h

FORMS    += mainwindow.ui
#winows
win32{
    BASEDIR = $${_PRO_FILE_PWD_}
    INCLUDEPATH += $${BASEDIR}
    PROJECT_FILE_PATH = $${_PRO_FILE_PWD_}
    ARCH = windows
    DEFINES += ARCH=\\\"$${ARCH}\\\"

    LUA_VERSION = 5.1

   # lua
    INCLUDEPATH += $${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/include
    LIBS += -L$${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/lib -llua

}
#UbuntuX86
linux-g++{
    BASEDIR = $${_PRO_FILE_PWD_}
    INCLUDEPATH += $${BASEDIR}
    PROJECT_FILE_PATH = $${_PRO_FILE_PWD_}
    ARCH = windows
    DEFINES += ARCH=\\\"$${ARCH}\\\"

    LUA_VERSION = x86

   # lua
    INCLUDEPATH += $${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/include
    LIBS += -L$${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/lib -llua

}
#ARM
linux-TIarmv7-sgx-g++{
    QT += opengl
    BASEDIR = $${_PRO_FILE_PWD_}
    INCLUDEPATH += $${BASEDIR}
    PROJECT_FILE_PATH = $${_PRO_FILE_PWD_}
    ARCH = windows
    DEFINES += ARCH=\\\"$${ARCH}\\\"

    LUA_VERSION = arm

   # lua
    INCLUDEPATH += $${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/include
    LIBS += -L$${PROJECT_FILE_PATH}/sysroot/$${ARCH}/lua-$${LUA_VERSION}/lib -llua

}
