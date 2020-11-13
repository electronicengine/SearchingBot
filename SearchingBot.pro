QT       += core gui charts network quickwidgets qml androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui charts network quickwidgets qml

CONFIG += c++14 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bot.cpp \
        botunittest.cpp \
        filelog.cpp \
        loging.cpp \
        logview.cpp \
        main.cpp \
        qmllistitem.cpp \
        qmllistobject.cpp \
        searchengine.cpp \
        searchprocessbox.cpp \
        searchqueueworker.cpp \
        searchwindow.cpp

HEADERS += \
    bot.h \
    botunittest.h \
    filelog.h \
    loging.h \
    logview.h \
    qmllistitem.h \
    qmllistobject.h \
    searchengine.h \
    searchprocessbox.h \
    searchqueueworker.h \
    searchwindow.h

ANDROID_EXTRA_LIBS += \
    /home/yusuf/Android/Sdk/android_openssl/latest/arm64/libcrypto_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/arm64/libssl_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/arm/libcrypto_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/arm/libssl_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/arm/libcrypto_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/x86/libssl_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/x86/libcrypto_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/x86_64/libssl_1_1.so \
    /home/yusuf/Android/Sdk/android_openssl/latest/x86_64/libcrypto_1_1.so


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    filelog.ui \
    logview.ui \
    searchprocessbox.ui \
    searchwindow.ui

RESOURCES += \
    resource.qrc

ANDROID_PACKAGE_SOURCE_DIR = /home/yusuf/Documents/workspace/SearchingBot


DISTFILES += \
    AndroidManifest.xml \
    images/add_pressed.png \
    images/add_unpressed.png \
    images/delete_pressed.png \
    images/delete_unpressed.png \
    images/down_pressed.png \
    images/down_unpressed.png \
    images/laser_locked.png \
    images/laser_unlocked.png \
    images/left_pressed.png \
    images/left_unpressed.png \
    images/pass_pressed.png \
    images/pass_previous_pressed.png \
    images/pass_previous_unpressed.png \
    images/pass_unpressed.png \
    images/refresh_pressed.png \
    images/refresh_unpressed.png \
    images/right_pressed.png \
    images/right_unpressed.png \
    images/searchingbot.png \
    images/show_pressed.png \
    images/searchingbot.png \
    images/show_unpressed.png \
    images/start_pressed.png \
    images/start_unpressed.png \
    images/stop_pressed.png \
    images/stop_unpressed.png \
    images/template.png \
    images/toggle_button_off.png \
    images/toggle_button_on.png \
    images/up_pressed.png \
    images/up_unpressed.png \
    images/wifi_locked.png \
    images/wifi_unlocked.png

ANDROID_ABIS = armeabi-v7a
