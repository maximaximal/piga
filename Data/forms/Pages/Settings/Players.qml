import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: 300
    height: 400
    color: "transparent"

    onFocusChanged: {
        if(focus) {
            playerList.focus = true
        }
    }

    ListView {
        id: playerList
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
        spacing: 5
        anchors.top: titleText.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 6
        model: playerManager

        delegate: PlayerDelegate {

        }

    }

    Text {
        id: titleText
        x: 8
        y: 8
        width: 284
        height: 24
        text: qsTr("Players")
        font.bold: true
        font.pixelSize: 18
    }
}
