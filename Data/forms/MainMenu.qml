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

    GameBox {
        y: root.height / 4
        width: root.width / 4
        height: root.height / 2
    }
    GameBox {
        x: root.width / 4 + 10
        y: root.height / 4
        width: root.width / 4
        height: root.height / 2
    }
}
