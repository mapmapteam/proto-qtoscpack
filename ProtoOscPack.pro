TEMPLATE = app

QT += qml quick
QT += quickcontrols2

CONFIG += c++11
CONFIG += qtquickcompiler # for better performances -- but it's only with the commercial Qt version (no op in the free version)

CONFIG += sdk_no_version_check # disable warning on macOS

SOURCES += main.cpp \
    oscsender.cpp \
    osc/OscOutboundPacketStream.cpp \
    osc/OscPrintReceivedElements.cpp \
    osc/OscReceivedElements.cpp \
    osc/OscTypes.cpp \
    controller.cpp \
    oscreceiver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    oscsender.h \
    osc/MessageMappingOscPacketListener.h \
    osc/OscException.h \
    osc/OscHostEndianness.h \
    osc/OscOutboundPacketStream.h \
    osc/OscPacketListener.h \
    osc/OscPrintReceivedElements.h \
    osc/OscReceivedElements.h \
    osc/OscTypes.h \
    controller.h \
    oscreceiver.h

