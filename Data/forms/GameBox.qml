import QtQuick 2.0
import com.pigaco.managing 1.0

Rectangle {
    id: gameBox
    width: 150
    height: 300

    Game {
        id: gameHost
    }

    Image {
        id: backgroundImage
        anchors.fill: parent
    }

    Text {
        id: gameTitle
        x: 10
        y: 10
        height: 14
        text: qsTr("Game Title")
        font.bold: true
        anchors.right: parent.right
        anchors.rightMargin: 10
        wrapMode: Text.WrapAnywhere
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 16
    }

    Text {
        id: gameDescription
        x: 10
        y: 30
        height: 14
        text: "This description is very long and interesting."
        textFormat: Text.AutoText
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        anchors.right: parent.right
        anchors.rightMargin: 10
        wrapMode: Text.WordWrap
        anchors.top: gameTitle.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 12
    }

    Text {
        id: author
        x: 10
        y: 256
        text: qsTr("Author")
        anchors.bottom: version.top
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 12
    }

    Text {
        id: version
        x: 10
        y: 276
        text: qsTr("V0.1")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pixelSize: 12
    }
}

