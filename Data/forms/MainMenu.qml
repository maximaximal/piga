import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    id: root
    width: Screen.width
    height: Screen.height
    color: "#000000"
    title: "Hello World!"

    ListView {
        id: gameList
        x: 0
        y: parent.height / 4
        width: parent.width
        height: parent.height / 2
        orientation: ListView.Horizontal
        spacing: 20

        model: dirScanner
        delegate: GameBox {
            width: 250
            height: parent.height
        }
    }
}
