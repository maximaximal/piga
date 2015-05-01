import QtQuick 2.0
import com.pigaco.managing 1.0

Rectangle {
    id: gameBox
    width: 150;
    height: 300;
    color: "white"

    border.width: activeFocus ? 5 : 0
    border.color: "blue"

    property Game gameHost: game;

    Keys.onReturnPressed: {
        if(activeFocus)
            game.start();
    }

    NumberAnimation on opacity {
        id: fadeInOpacity
        duration: 500
        from: 0
        to: 1
    }
    NumberAnimation on scale {
        id: fadeInScale
        duration: 800
        from: 0
        to: 1
        easing.type: Easing.OutExpo
    }

    Component.onCompleted: {
        fadeInScale.start()
        fadeInOpacity.start()
    }

    opacity: 1

    Image {
        id: backgroundImg
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
        source: backgroundImage
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

    Image {
        id: image1
        x: 134
        y: -16
        width: 32
        height: 32
        fillMode: Image.PreserveAspectFit
        anchors.right: parent.right
        anchors.rightMargin: -16
        anchors.top: parent.top
        anchors.topMargin: -16
        source: logoImage
    }
}

