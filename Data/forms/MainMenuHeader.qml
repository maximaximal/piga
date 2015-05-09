import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.2

Rectangle {
    id: mainMenuHeader
    width: 900
    height: 150
    color: "#00000000"
    opacity: 1

    signal storeClicked
    signal settingsClicked

    onFocusChanged: {
        if(mainMenuHeader.focus) {
            store.focus = true
        }
    }

    Text {
        id: settings
        x: 252
        text: qsTr("Settings")
        styleColor: "#779bd6"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 56
        anchors.top: parent.top
        anchors.topMargin: 56
        font.bold: true
        anchors.left: store.right
        anchors.leftMargin: 60
        font.pixelSize: 32
        style: activeFocus ? Text.Outline : Text.Normal

        KeyNavigation.right: quit
        KeyNavigation.left: store

        Keys.onReturnPressed: {
            settingsClicked();
        }

        Behavior on scale {
            NumberAnimation {
                target: settings
                properties: "scale"
                duration: 300
                easing.type: Easing.OutBack
            }
        }
        scale: activeFocus ? 1.05 : 1
    }

    Text {
        id: store
        width: 101
        text: qsTr("Store")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 56
        anchors.top: parent.top
        anchors.topMargin: 56
        anchors.left: parent.left
        anchors.leftMargin: 50
        font.bold: true
        font.pixelSize: 32
        styleColor: "#779bd6"
        style: activeFocus ? Text.Outline : Text.Normal

        KeyNavigation.right: settings
        KeyNavigation.left: quit

        Keys.onReturnPressed: {
            storeClicked();
        }

        Behavior on scale {
            NumberAnimation {
                target: store
                properties: "scale"
                duration: 300
                easing.type: Easing.OutBack
            }
        }
        scale: activeFocus ? 1.05 : 1
    }

    Text {
        id: quit
        x: 249
        y: 2
        text: qsTr("Quit")
        scale: activeFocus ? 1.05 : 1
        anchors.bottomMargin: 56
        anchors.top: parent.top
        anchors.leftMargin: 60
        font.bold: true
        anchors.bottom: parent.bottom
        styleColor: "#779bd6"
        anchors.left: settings.right
        style: activeFocus ? Text.Outline : Text.Normal
        anchors.topMargin: 56
        font.pixelSize: 32

        KeyNavigation.right: store
        KeyNavigation.left: settings

        Keys.onReturnPressed: {
            Qt.quit();
        }
    }

}

