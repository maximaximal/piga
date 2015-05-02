import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root
    width: 800
    height: 900

    Text {
        id: text1
        x: 324
        width: 425
        height: 65
        text: qsTr("The store has not been implemented yet.")
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: 166
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 56
    }

    Text {
        id: text2
        x: 387
        y: 450
        text: qsTr("Thank you for your interest though! :)")
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 18
    }

    Text {
        id: text3
        x: 387
        y: 699
        text: qsTr("Back")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 152
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pixelSize: 42

        focus: true

        color: activeFocus ? "#779bd6" : "black";

        Keys.onReturnPressed: root.parent.source = ""
    }

}

