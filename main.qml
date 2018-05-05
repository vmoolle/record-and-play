import QtQuick 2.7

Item {
    id: root
    ToggleButton {
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        height: parent.height

        text: toggled? "RECORDING": "RECORD"

        onRequestToggle: toggled = !toggled
    }
    ToggleButton {
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        height: parent.height

        text: toggled? "PLAYING": "PLAY"

        onRequestToggle: toggled = !toggled
    }
}
