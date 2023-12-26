#包含一个目录
INCLUDEPATH += $$PWD
#如果DEPENDPATH目录里的头文件发生了变化，所有的cpp都会重新编译
DEPENDPATH += $$PWD

#$$PWD  当前目录
HEADERS += \
    $$PWD/animationstackedwidget.h \
    $$PWD/customwidget.h \
    $$PWD/mlineedit.h


SOURCES += \
    $$PWD/animationstackedwidget.cpp \
    $$PWD/customwidget.cpp \
    $$PWD/mlineedit.cpp


FORMS += \
