import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Window {
    title: qsTr("OSC")
    width: 320
    height: 240
    visible: true

    function handleMessageReceived(oscPath, oscArguments) {
        console.log("QML-Received OSC: " + oscPath + " " + oscArguments);
    }

    Connections {
        target: controller

        onMessageReceived: {
            handleMessageReceived(oscPath, oscArguments);
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#ffcc33"
        Button {
            text: "Push Me"
            anchors.centerIn: parent
            onClicked: {
                controller.sendSomething("/hello", [123, 3.14159, "from QML"]);
            }
        }
    }
}
