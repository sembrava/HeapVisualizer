import QtQuick 2.15
import QtQuick.Controls 2.15
import "../logic/Colors.js" as Colors

Button {
    id: styledButton

    contentItem: Text {
        text: styledButton.text
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        radius: 5
        color: styledButton.hovered ? Colors.getHoveredButtonColor() : Colors.getButtonColor()
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            styledButton.clicked()
        }
    }
}
