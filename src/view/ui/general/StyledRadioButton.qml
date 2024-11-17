import QtQuick 2.15
import QtQuick.Controls 2.15
import "../logic/Colors.js" as Colors

RadioButton {
    id: styledRadioButton
    scale: 0.8
    opacity: enabled ? 1 : 0.5

    contentItem: Text {
        text: styledRadioButton.text
        color: Colors.getTextColor()
        leftPadding: styledRadioButton.indicator.width + styledRadioButton.spacing
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked:  {
            styledRadioButton.checked = !styledRadioButton.checked
        }
    }
}
