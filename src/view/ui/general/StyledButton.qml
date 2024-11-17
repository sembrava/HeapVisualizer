import QtQuick 2.15
import QtQuick.Controls 2.15
import "../logic/Colors.js" as Colors

Button {
    id: styledButton

    property string color: Colors.getButtonColor()
    property string hoverColor: Colors.getHoveredButtonColor()
    property string activeColor: Colors.getActiveButtonColor()
    property string fontColor: Colors.getButtonTextColor()
    property int fontSize: 14
    property bool bold: false
    property int radius: 5

    opacity: enabled ? 1 : 0.5

    contentItem: Text {
        text: styledButton.text
        color: styledButton.fontColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        font.pixelSize: styledButton.fontSize
        font.bold: styledButton.bold
    }

    background: Rectangle {
        radius: styledButton.radius
        color: styledButton.pressed
                   ? styledButton.activeColor
                   : (styledButton.hovered && styledButton.enabled
                       ? styledButton.hoverColor
                       : styledButton.color)
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            styledButton.clicked()
        }
    }
}
