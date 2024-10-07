import QtQuick 2.15
import QtQuick.Controls 2.15
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
                newVisualizationPopup.open()
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

                        }
                    }

                    HoverButton {
                        id: openButton
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        text: qsTr("Open")

                        onClicked: {
                            globals.currentFileName = modelData.name
                            globals.currentlyEditedTree = modelData.tree

                            switchPage("Editor")
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: newVisualizationPopup
        width: 350
        height: 300
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true

        background: Rectangle {
            color: "white"
            border.color: "#bbb"
            radius: 5
        }

        Text {
            id: popupTitle
            text: qsTr("Create visualization")
        }

        HoverButton {
            anchors.right: parent.right
            text: "x"

            onClicked: {
                newVisualizationPopup.close()
            }
        }

        Column {
            anchors.topMargin: 10
            anchors.top: popupTitle.bottom
            spacing: 10

            RadioButton {
                id: openEditorRadioButton
                text: qsTr("Open editor")
                checked: true
            }

            RadioButton {
                id: generateRandomRadioButton
                text: qsTr("Generate randomly")
            }

            Row {
                x: 20
                spacing: 10

                Text {
                    text: qsTr("Array size")
                    color: generateRandomRadioButton.checked ? "#000" : "#ccc"
                }

                Rectangle {
                    anchors.leftMargin: 10
                    width: 50
                    height: randomArrayLength.implicitHeight
                    border.color: generateRandomRadioButton.checked ? "#ccc" : "#eee"
                    radius: 3

                    TextInput {
                        id: randomArrayLength
                        width: parent.width
                        padding: 2
                        enabled: generateRandomRadioButton.checked
                        text: "15"
                        color: generateRandomRadioButton.checked ? "#000" : "#ccc"
                    }
                }
            }

            RadioButton {
                id: fromArrayRadioButton
                text: qsTr("Create from array")
            }

            Rectangle {
                x: 20
                anchors.leftMargin: 10
                width: 200
                height: randomArrayLength.implicitHeight
                border.color: fromArrayRadioButton.checked ? "#ccc" : "#eee"
                radius: 3

                TextInput {
                    id: customArray
                    width: parent.width
                    padding: 2
                    enabled: fromArrayRadioButton.checked
                    color: fromArrayRadioButton.checked ? "#000" : "#ccc"
                }
            }
        }

        HoverButton {
            text: qsTr("Create")
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                if (openEditorRadioButton.checked) {
                    switchPage("Editor")
                }

                else if (generateRandomRadioButton.checked) {
                    globals.currentlyEditedTree = homeModel.generateRandomArray(Number(randomArrayLength.text))
                    switchPage("Editor")
                }

                else if (fromArrayRadioButton.checked) {
                    globals.currentlyEditedTree = customArray.text.split(",").map(num => Number(num))
                    switchPage("Editor")
                }
            }
        }
    }
}
