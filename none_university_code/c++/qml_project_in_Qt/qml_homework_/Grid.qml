
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle {
    Component {
           id: contactDelegate
           Item {
               width: grid.cellWidth; height: grid.cellHeight
               Column {
                   anchors.fill: parent
                   Image {
                       anchors.fill: parent
                       property string filePath: "file:/" + role1
                       source : filePath }
               }
           }
       }

       GridView {
           id: grid
           anchors.fill: parent
           cellWidth: parent.width/3; cellHeight: parent.height/2

           model: myModel
           delegate: contactDelegate
           ScrollBar.vertical: ScrollBar {
               id: scrollBar
               active: true
               width: 20
           }

       }
}


