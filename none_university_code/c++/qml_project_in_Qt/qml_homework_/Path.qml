import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


Rectangle {
    property int itemSize: parent.height/4

    PathView {
        id: view
        pathItemCount: 6
        anchors.fill: parent
        model: myModel

        path: Path {
            startX: 0
            startY: height

            PathAttribute { name: "size"; value: itemSize }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathCurve {
                x: view.width / 5
                y: view.height / 2
            }
            PathCurve {
                x: view.width / 5 * 2
                y: view.height / 4
            }
            PathAttribute { name: "size"; value: itemSize }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathPercent { value: 0.49 }

            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "size"; value: itemSize * 2 }
            PathAttribute { name: "opacity"; value: 1 }
            PathLine {
                x: view.width / 5 * 3
                y: view.height / 4
            }
            PathAttribute { name: "size"; value: itemSize * 2 }
            PathAttribute { name: "opacity"; value: 1 }
            PathPercent { value: 0.51 }

            PathLine { relativeX: 0; relativeY: 0 }

            PathAttribute { name: "size"; value: itemSize }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathCurve {
                x: view.width / 5 * 4
                y: view.height / 2
            }
            PathCurve {
                x: view.width
                y: view.height
            }
            PathPercent { value: 1 }
            PathAttribute { name: "size"; value: itemSize }
            PathAttribute { name: "opacity"; value: 0.5 }
        }
        delegate: Image {
            width: PathView.size
            height: PathView.size
            property string filePath: "file:/" + role1
            source : filePath
        }
    }
}
