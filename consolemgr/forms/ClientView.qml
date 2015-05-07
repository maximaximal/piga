import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3

import com.pigaco.networking 1.0

Rectangle {
    property Client client

    Layout.fillWidth: true
    Layout.fillHeight: true

    ListModel {
        id: gamesListModel
    }

    TabView {
        anchors.fill: parent

        Tab {
            title: "Games"
            ListView {
                model: gamesListModel
            }
        }

        Tab {
            title: "Users"
            ListView {
                id: usersList
                model: client.users
            }
        }
    }
}

