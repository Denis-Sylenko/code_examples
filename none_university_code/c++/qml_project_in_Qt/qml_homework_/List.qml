import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        ListView {
            id: list
            width: root.width
            height: root.height
            spacing: 2
            model: myModel

            delegate: Component {
                Item {
                    width: list.width
                    height: list.height

                    id: myItem
                    Image {
                        anchors.fill:myItem
                        property string filePath: "file:/" + role1
                        source : filePath
                      }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.currentIndex = index
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                active: true
                width: 20
            }
            highlightMoveDuration: 50
        }
    }
}
