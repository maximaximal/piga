import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    id: root
    title: "Hello World!"

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
    }

    toolBar: ToolBar {
        RowLayout {

        }
    }
}

