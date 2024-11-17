import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../logic/Colors.js" as Colors

Button {
    property bool selected: false
    required property string source
    required property string title

    id: sidebarButton
    width: 65
    height: 65

    background: Rectangle {
        id: container
        radius: 5
        opacity: enabled || selected ? 1 : 0.5
        color: sidebarButton.selected
                   ? Colors.getButtonColor()
                   : sidebarButton.hovered && sidebarButton.enabled
                       ? Colors.getHoveredButtonColor()
                       : Colors.getButtonColor()

        Rectangle {
            height: sidebarButton.height - 11
            width: 3
            x: -7
            visible: sidebarButton.selected
            color: Colors.getActiveButtonColor()
        }

        ColumnLayout {
            id: content
            anchors.centerIn: parent
            anchors.topMargin: 5

            Image {
                source: sidebarButton.source
                Layout.alignment: Qt.AlignCenter
            }

            Text {
                text: sidebarButton.title
                color: Colors.getButtonTextColor()
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 11
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            sidebarButton.clicked()
        }
    }
}

