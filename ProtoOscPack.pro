TEMPLATE = app

QT += qml quick
QT += quickcontrols2

CONFIG += c++11
CONFIG += qtquickcompiler
# for better performances -- but it's only with the commercial Qt version (no op in the free version)

CONFIG += sdk_no_version_check # disable warning on macOS

SOURCES += main.cpp \
    oscsender.cpp \
    oscreceiver.cpp \
    contrib/oscpack/OscOutboundPacketStream.cpp \
    contrib/oscpack/OscPrintReceivedElements.cpp \
    contrib/oscpack/OscReceivedElements.cpp \
    contrib/oscpack/OscTypes.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    oscsender.h \
    oscreceiver.h \
    contrib/oscpack/MessageMappingOscPacketListener.h \
    contrib/oscpack/OscException.h \
    contrib/oscpack/OscHostEndianness.h \
    contrib/oscpack/OscOutboundPacketStream.h \
    contrib/oscpack/OscPacketListener.h \
    contrib/oscpack/OscPrintReceivedElements.h \
    contrib/oscpack/OscReceivedElements.h \
    contrib/oscpack/OscTypes.h

