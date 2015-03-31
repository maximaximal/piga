import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
    id: connectionWindow
    title: qsTr("New Connection")
    width: 250
    height: 200

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

            Layout.fillWidth: true
            KeyNavigation.tab: user
        }
        Text {
            id: userLabel
            text: qsTr("User")
            font.pixelSize: 12
            Layout.minimumWidth: 80
        }
        TextInput {
            id: user
            width: 80
            height: 20
            text: qsTr("Admin")
            font.pixelSize: 12
            selectByMouse: true

            Layout.fillWidth: true
            KeyNavigation.tab: password
        }
        TextInput {
            id: passwordLabel
            text: qsTr("Password")
            font.pixelSize: 12
            Layout.minimumWidth: 80
        }
        TextInput {
            id: password
            width: 80
            height: 20
            text: qsTr("Password")
            font.pixelSize: 12
            selectByMouse: true
            echoMode: TextInput.Password

            Layout.fillWidth: true
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
            text: "Connect"
            Layout.minimumWidth: 60
        }
        Button {
            text: "Abort"
            Layout.minimumWidth: 60

            onClicked: connectionWindow.close()
        }
    }
}

