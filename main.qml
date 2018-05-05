import QtQuick 2.7

Item {
    id: root
    ToggleButton {
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        height: parent.height

        toggled: recordAndPlay.recording
        text: toggled? "RECORDING": "RECORD"
        onRequestToggle: recordAndPlay.requestRecordingToggle()
    }
    ToggleButton {
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        height: parent.height

        toggled: recordAndPlay.playing
        text: toggled? "PLAYING": "PLAY"
        onRequestToggle: recordAndPlay.requestPlayingToggle()
    }
}
