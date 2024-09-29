import QtQuick 2.15
import "../general"

Item {
    property var homeModel: modelManager.createHomePageModel()

    signal switchPage(string pageName)

    Column {
        id: homePageContainer
        anchors.fill: parent
        spacing: 10
        padding: 10

        HoverButton {
            id: createVisualizationButton
            width: 200

            Text {
                anchors.centerIn: parent
                text: qsTr("Create visualization")
            }

            onClicked: {
                switchPage("Editor")
            }
        }

        Rectangle {
            id: homePageDivider
            width: parent.width - 20
            height: 1
            color: "#cccccc"
        }

        Grid {
            id: savedVisualizationsContainer
            columns: 4
            spacing: 10

            Repeater {
                id: savedVisualizationsRepeater
                model: homeModel.savedVisualizations

                delegate: Rectangle {
                    color: "#cccccc"
                    width: 200
                    height: 100
                    radius: 5
                    clip: true

                    Rectangle {
                        width: parent.width
                        height: 20
                        color: "#bbbbbb"
                        radius: 5

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            x: 5
                            color: "white"
                            text: modelData.name
                        }
                    }

                    HoverButton {
                        id: deleteButton
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        text: "x"

                        onClicked: {
                            homeModel.deleteVisualization(index)
                        }
                    }

                    HoverButton {
                        id: openButton
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        text: qsTr("Open")
                    }
                }
            }
        }
    }
}
