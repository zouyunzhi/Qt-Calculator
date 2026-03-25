QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custombutton.cpp \
    inputbox.cpp \
    main.cpp \
    calculator.cpp

HEADERS += \
    calculator.h \
    custombutton.h \
    exprtk.hpp \
    inputbox.h

FORMS += \
    calculator.ui

TRANSLATIONS += \
    translations/en_US.ts \
    translations/es_ES.ts \
    translations/fr_FR.ts \
    translations/de_DE.ts \
    translations/it_IT.ts \
    translations/pt_PT.ts \
    translations/ru_RU.ts \
    translations/ja_JP.ts \
    translations/ko_KR.ts \
    translations/ar_SA.ts \
    translations/hi_IN.ts \
    translations/th_TH.ts \
    translations/vi_VN.ts \
    translations/nl_NL.ts \
    translations/sv_SE.ts \
    translations/zh_CN.ts \
    translations/zh_TW.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32-msvc* {
    QMAKE_CXXFLAGS += /bigobj
}
