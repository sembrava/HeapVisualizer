import QtQuick 2.15
import "../logic/Colors.js" as Colors

Rectangle {
    default property alias content: contentItem.data

    width: parent.width
    color: Colors.getSectionColor()
    radius: 5
    implicitHeight: contentItem.implicitHeight + 20

    Rectangle {
        id: contentItem
        anchors.fill: parent
        anchors.margins: 10
        color: "transparent"
        implicitHeight: childrenRect.height
    }
}
