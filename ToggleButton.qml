import QtQuick 2.0

Item {
    id: root

    signal requestToggle

    property bool toggled

    property string text
    property color color: "lightblue"
    property color toggledColor: "pink"

    property double fontPixelSize: 20
    property double toggledScale: 0.85

    Rectangle {
        anchors.fill: parent

        property double toggleMargins: (1 - root.toggledScale)*Math.min(root.width, root.height)/2
        anchors.margins: root.toggled? toggleMargins: 0

        color: root.toggled? root.toggledColor: root.color

        Text {
            anchors.centerIn: parent
            text: root.text
            font.pixelSize: root.fontPixelSize
        }
    }

    MouseArea {
        id: area
        anchors.fill: parent
        onPressed: root.requestToggle()
    }
}
