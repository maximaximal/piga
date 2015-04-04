import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
    id: connectionWindow
    title: qsTr("New Connection")
    width: 250
    height: 200

    signal dataEntered(string host, int port)

    GridLayout {
        id: mainGrid

        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            top: parent.top
            topMargin: 10
        }

        layoutDirection: Qt.LeftToRight
        columns: 2

        Text {
            id: hostLabel
            text: qsTr("Host:")
            font.pixelSize: 12
            Layout.minimumWidth: 80
        }
        TextInput {
            id: host
            width: 80
            height: 20
            text: qsTr("pigaco.console.org")
            font.pixelSize: 12
            selectByMouse: true
            inputMethodHints: Qt.ImhUrlCharactersOnly

            Layout.fillWidth: true
            KeyNavigation.tab: port
        }
        Text {
            id: portLabel
            text: qsTr("Port:")
            font.pixelSize: 12
            Layout.minimumWidth: 80
        }
        TextInput {
            id: port
            text: qsTr("17010")
            width: 80
            height: 20
            font.pixelSize: 12
            selectByMouse: true
            inputMethodHints: Qt.ImhDigitsOnly

            Layout.fillWidth: true
            KeyNavigation.tab: user
        }
    }
    RowLayout {
        spacing: 10

        anchors {
            right: parent.right;
            rightMargin: 10;
            bottom: parent.bottom;
            bottomMargin: 10
        }

        Button {
            id: connectButton
            text: "Connect"
            Layout.minimumWidth: 60
            isDefault: true

            Keys.onReturnPressed: {
                dataEntered(host.text, port.text)
            }

            onClicked: {
                dataEntered(host.text, port.text)
            }
        }
        Button {
            id: abortButton
            text: "Abort"
            Layout.minimumWidth: 60

            Keys.onReturnPressed: connectionWindow.close()
            onClicked: connectionWindow.close()
        }
    }
}

