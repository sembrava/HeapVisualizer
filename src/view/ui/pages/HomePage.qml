import QtQuick 2.15
import QtQuick.Controls 2.15
import "../general"
import "../logic/Utils.js" as Utils

Item {
    property var homeModel: modelManager.createHomePageModel()

    signal switchPage(string pageName)

    HoverButton {
        width: 100
        anchors.right: parent.right
        anchors.rightMargin: 10
        y: 10
        text: globals.language === "hu" ? "Beállítások" : "Settings"

        onClicked: {
            switchPage("Settings")
        }
    }

    Column {
        id: homePageContainer
        anchors.fill: parent
        spacing: 10
        padding: 10

        HoverButton {
            id: createVisualizationButton
            width: 200
            text: globals.language === "hu" ? "Új szemléltetés" : "Create visualization"

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

        ScrollView {
            width: parent.width
            height: parent.height

            Grid {
                id: savedVisualizationsContainer
                columns: 4
                spacing: 10

                Repeater {
                    id: savedVisualizationsRepeater
                    model: homeModel.savedVisualizations

                    delegate: Rectangle {
                        color: "#cccccc"
                        width: 209
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
                            text: globals.language === "hu" ? "Megnyitás" : "Open"

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

        onClosed: {
            customArrayError.visible = false
        }

        Text {
            id: newVisualizationTitle
            text: globals.language === "hu" ? "Új szemléltetés" : "Create visualization"
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
            anchors.top: newVisualizationTitle.bottom
            spacing: 10

            RadioButton {
                id: openEditorRadioButton
                text: globals.language === "hu" ? "Szerkesztő megnyitása" : "Open editor"
                checked: true
            }

            RadioButton {
                id: generateRandomRadioButton
                text: globals.language === "hu" ? "Véletlenszerű tömb generálása" : "Generate randomly"
            }

            Row {
                x: 20
                spacing: 5

                Text {
                    text: globals.language === "hu" ? "Tömb mérete" : "Array size"
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

                        validator: RegularExpressionValidator {
                            regularExpression: /^[1-9]$|^1[0-5]$/
                        }
                    }
                }
            }

            RadioButton {
                id: fromArrayRadioButton
                text: globals.language === "hu" ? "Generálás tömb megadásával" : "Create from array"

                onCheckedChanged: {
                    if (!checked)
                        customArrayError.visible = false
                }
            }

            Rectangle {
                id: customArrayContainer
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

                Text {
                    id: customArrayError
                    text: globals.language === "hu" ? "A bemenet egy maximum 15 hosszú, -999 és 999 közötti értékekből \nálló, vesszővel elválasztott lista legyen" : "Input must be at most 15 comma separated numbers from -999 to 999"
                    font.pixelSize: 10
                    color: "red"
                    y: 20
                    visible: false
                }
            }
        }

        HoverButton {
            text: globals.language === "hu" ? "Létrehozás" : "Create"
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                if (fromArrayRadioButton.checked && !Utils.isValidArrayLiteral(customArray.text)) {
                    customArrayError.visible = true
                    return;
                }

                globals.currentFileName = ""
                globals.currentlyEditedTree = []

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
