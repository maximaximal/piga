import QtQuick 2.0

Rectangle {
    id: rectangle1
    width: 200
    height: 30
    color: playerNameTextEdit.activeFocus ? "steelblue" : "transparent"

    onFocusChanged: {
        if(focus) {
            playerNameTextEdit.focus = true
        }
    }

    TextInput {
        id: playerNameTextEdit
        y: 5
        height: 20
        text: playerName
        inputMask: qsTr("")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: playerIDText.right
        anchors.leftMargin: 6
        font.pixelSize: 17

        onTextChanged: {
            playerManager.playerNameChanged(playerNameTextEdit.text, playerID);
        }
    }

    Text {
        id: playerIDText
        y: 5
        width: 14
        height: 20
        text: playerID
        anchors.left: parent.left
        anchors.leftMargin: 8
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        font.pixelSize: 17
    }
}

