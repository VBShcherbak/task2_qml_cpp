import QtQuick 2.15

Rectangle {
    id: root
    color: "#ea7025"
    border.color: "lightsteelblue"
    border.width: 4
    radius: 4
    property alias text: label.text
    signal swap(int indSwap)

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked:  {
            swap(index);
        }
    }

    Text {
        id: label
        anchors.centerIn: parent
        color: "#ececec"
        font.pixelSize: root.width/2
    }
}
