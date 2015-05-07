import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

import com.pigaco.networking 1.0


ApplicationWindow {
    id: root
    title: "Hello World!"

    //The connection window (if open)
    property NewConnection connectionWindow

    // The currently active client.
    property Client currentClient

    signal activeClientChanged(Client client)

    connectionWindow: NewConnection {
        onDataEntered: {
            clientMgr.newConnection(host, port)
        }
    }

    width: 800
    height: 600

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Close"
                onTriggered: root.close()
            }
        }
        Menu {
            title: "Connection"
            MenuItem {
                text: "Connect to host"
                onTriggered: {
                    connectionWindow.show()
                }
            }
        }
    }

    toolBar: ToolBar {
        RowLayout {

        }
    }

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        spacing: 20

        ListView {
            id: listView
            snapMode: ListView.SnapToItem

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 80
            Layout.maximumWidth: 200

            model: clientMgr

            delegate: Item {
                id: clientsListDelegate
                width: listView.width
                height: 20
                property Client client: netClient
                Text {
                    text: name
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.currentIndex = index
                }
            }

            highlight: Rectangle {
                height: 20
                width: listView.width
                color: "lightsteelblue"
            }

            onCurrentIndexChanged: {
                currentClient = listView.itemAt(0, currentIndex).client;
                activeClientChanged(currentClient);
            }
        }
        ClientView {
            client: currentClient
        }
    }
}

