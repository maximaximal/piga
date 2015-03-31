import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

import com.pigaco.networking 1.0


ApplicationWindow {
    id: root
    title: "Hello World!"

    property variant connectionWindow;

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
                    var conn = Qt.createComponent("NewConnection.qml")
                    connectionWindow = conn.createObject(root)
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

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 80

            model: ListModel {
                id: connectionsListModel
            }

            delegate: Text {
                text: name
            }
        }

        TabView {
            id: tabView

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 200

            Tab {
                title: "Users"
            }
            Tab {
                title: "Games"
            }
            Tab {
                title: "Log"
            }
        }
    }
}

