import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: hoverButton

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            hoverButton.clicked()
        }
    }

    signal clicked()
}
