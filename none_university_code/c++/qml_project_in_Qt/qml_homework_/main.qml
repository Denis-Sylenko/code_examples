import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import QtQuick.Controls 2.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Gallery")
    minimumHeight: 250
    minimumWidth: 250
    Loader
    {
         id: loader
         anchors.fill: parent
         source: "Grid.qml"
     }
    property bool itemsVisible: true

       Menu {
           id: contextmenu
           x: (parent.width - contextmenu.width) / 2
           y: (parent.height - contextmenu.height) / 2
           modal: true

           MenuItem {
               text: "List"
               onClicked: loader.source ="List.qml"
           }
           MenuItem {
               text: "Grid"
               onClicked: loader.source ="Grid.qml"
           }
           MenuItem {
               text: "Path"
               onClicked: loader.source ="Path.qml"
           }
       }

       Button {
           text: "Menu"
           onClicked: {
               itemsVisible = !itemsVisible
               contextmenu.open()
           }
       }
   }

