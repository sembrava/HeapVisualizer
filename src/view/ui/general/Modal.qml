import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../logic/Colors.js" as Colors

Popup {
    property string title: ""
    property alias body: bodyItem.data
    property alias footer: footerItem.data

    id: modal
    modal: true
    focus: true
    anchors.centerIn: Overlay.overlay
    width: content.implicitWidth + 20
    height: content.implicitHeight + 20

    background: Rectangle {
        color: Colors.getSectionColor()
        radius: 5
    }

    Column {
        id: content
        anchors.fill: parent
        spacing: 10
        width: children.implicitWidth

        Text {
            text: title
            font.bold: true
            font.pixelSize: 18
            color: Colors.getTextColor()
        }

        Column {
            id: bodyItem
            width: childrenRect.width
            height: childrenRect.height
        }

        RowLayout {
            id: footerItem
            width: modal.width - 20
            height: childrenRect.height
        }
    }
}
