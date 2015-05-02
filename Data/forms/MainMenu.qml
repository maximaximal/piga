import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    id: root
    width: Screen.width
    height: Screen.height
    color: "#85c562"
    title: "PiGaCo"


    MainMenuHeader {
        id: header
        width: parent.width
        height: 120

        KeyNavigation.down: gameList

        onStoreClicked: {
            pageLoader.source = "Pages/Store/Main.qml"
            pageLoader.focus = true
        }
        onSettingsClicked: {
            pageLoader.source = "Pages/Settings/Main.qml"
            pageLoader.focus = true
        }
    }

    ListView {
        id: gameList
        x: 0
        y: parent.height / 4
        width: parent.width
        height: parent.height / 2
        orientation: ListView.Horizontal
        spacing: 20
        focus: true

        KeyNavigation.up: header

        model: dirScanner
        delegate: GameBox {
            width: 250
            height: parent.height
        }

    }
    Loader {
        id: pageLoader
        anchors.fill: parent

        onSourceChanged: {
            header.focus = true
        }

    }
}
