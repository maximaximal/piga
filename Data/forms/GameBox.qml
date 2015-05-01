import QtQuick 2.0
import com.pigaco.managing 1.0

Rectangle {
    id: gameBox
    width: 150;
    height: 300;
    color: "white"

    Image {
        id: backgroundImage
        anchors.fill: parent
    }

    Text {
        id: gameTitleText
        x: 10
        y: 10
        height: 14
        text: name
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
        text: description
        textFormat: Text.AutoText
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        anchors.right: parent.right
        anchors.rightMargin: 10
        wrapMode: Text.WordWrap
        anchors.top: gameTitleText.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 12
    }

    Text {
        id: authorText
        x: 10
        y: 256
        text: "Made by " + author
        anchors.bottom: versionText.top
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 12
    }

    Text {
        id: versionText
        x: 10
        y: 276
        text: "Version " + version
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pixelSize: 12
    }
}

