import QtQuick 2.15
import QtQuick.Controls 2.15
import "../logic/Colors.js" as Colors

Button {
    id: customButton

    background: Rectangle {
        radius: 5
        color: customButton.hovered ? Colors.getHoveredButtonColor() : Colors.getButtonColor()
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            customButton.clicked()
        }
    }
}
