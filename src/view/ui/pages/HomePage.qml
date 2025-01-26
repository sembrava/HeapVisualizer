import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../general"
import "../logic/Utils.js" as Utils
import "../logic/Colors.js" as Colors

Item {
    property var homeModel: modelManager.createHomePageModel()

    signal switchPage(string pageName)

    Column {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        Section {
            id: homePageHeader

            content: RowLayout {
                width: parent.width
                height: createVisualizationButton.height

                StyledButton {
                    id: createVisualizationButton
                    width: 300
                    bold: true
                    text: globals.language === "hu" ? "Új szemléltetés" : "Create visualization"
                    color: Colors.getMainButtonColor()
                    hoverColor: Colors.getHoveredMainButtonColor()

                    onClicked: {
                        newVisualizationPopup.open()
                    }
                }

                StyledButton {
                    Layout.alignment: Qt.AlignRight
                    id: settingsButton
                    width: 150
                    text: globals.language === "hu" ? "Beállítások / Settings" : "Settings / Beállítások"

                    onClicked: {
                        switchPage("Settings")
                    }
                }
            }
        }

        Section {
            id: savedVisualizations
            height: parent.height - homePageHeader.height - 10

            Rectangle {
                anchors.fill: parent
                visible: homeModel.savedVisualizations.length === 0
                color: "transparent"

                Text {
                    y: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: globals.language === "hu" ? "Az elmentett fák itt fognak megjelenni" : "Saved trees will appear here"
                    color: Colors.getLighterTextColor()
                    visible: homeModel.savedVisualizations.length === 0
                    opacity: 0.5
                    font.pixelSize: 16
                }
            }

            content: ScrollView {
                anchors.fill: parent

                Column {
                    id: savedVisualizationsContainer
                    anchors.fill: parent
                    spacing: 10

                    Repeater {
                        id: savedVisualizationsRepeater
                        model: homeModel.savedVisualizations

                        delegate: Rectangle {
                            color: Colors.getPrimaryDetailColor()
                            width: savedVisualizationsContainer.width
                            height: savedVisualizationRow.height
                            radius: 5

                            RowLayout {
                                id: savedVisualizationRow
                                anchors.fill: parent
                                anchors.leftMargin: 5
                                anchors.rightMargin: 5
                                height: openButton.height

                                Text {
                                    text: modelData.name
                                    font.pixelSize: 16
                                    color: Colors.getTextColor()
                                }

                                RowLayout {
                                    height: openButton.height
                                    Layout.alignment: Qt.AlignRight

                                    StyledButton {
                                        id: openButton
                                        text: globals.language === "hu" ? "Megnyitás" : "Open"

                                        onClicked: {

                                            globals.currentFileName = modelData.name
                                            globals.currentlyEditedTree = modelData.tree

                                            switchPage("Editor")
                                        }
                                    }

                                    StyledButton {
                                        id: deleteButton
                                        text: globals.language === "hu" ? "Törlés" : "Delete"
                                        fontColor: Colors.getTextColor()
                                        color: Colors.getRedButtonColor()
                                        hoverColor: Colors.getHoveredRedButtonColor()
                                        activeColor: Colors.getActiveRedButtonColor()

                                        onClicked: {
                                            homeModel.deleteVisualization(index)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Modal {
        id: newVisualizationPopup
        width: 400
        title: globals.language === "hu" ? "Új szemléltetés" : "New visualization"

        onClosed: {
            customArrayError.opacity = 0
        }

        body: Column {
            id: content
            spacing: 10
            width: children.implicitWidth

            StyledRadioButton {
                id: openEditorRadioButton
                text: globals.language === "hu" ? "Szerkesztő megnyitása" : "Open editor"
                checked: true
                x: 5
            }

            StyledRadioButton {
                id: generateRandomRadioButton
                text: globals.language === "hu" ? "Véletlenszerű tömb generálása" : "Generate randomly"
            }

            Row {
                spacing: 5
                x: 40

                Text {
                    text: globals.language === "hu" ? "Tömb mérete" : "Array size"
                    color: Colors.getTextColor()
                    opacity: generateRandomRadioButton.checked ? 1 : 0.5
                }

                Rectangle {
                    width: 50
                    height: randomArrayLength.implicitHeight
                    border.color: Colors.getBorderColor()
                    opacity: generateRandomRadioButton.checked ? 1 : 0.5
                    color: Colors.getTextInputColor()
                    radius: 3

                    TextInput {
                        id: randomArrayLength
                        width: parent.width
                        padding: 2
                        clip: true
                        enabled: generateRandomRadioButton.checked
                        text: "15"
                        color: Colors.getTextColor()
                        opacity: enabled ? 1 : 0.5

                        validator: RegularExpressionValidator {
                            regularExpression: /^[1-9]$|^1[0-5]$/
                        }
                    }
                }
            }

            StyledRadioButton {
                id: fromArrayRadioButton
                text: globals.language === "hu" ? "Generálás tömb megadásával" : "Create from array"

                onCheckedChanged: {
                    if (!checked)
                        customArrayError.opacity = 0
                }
            }

            Column {
                spacing: 10
                x: 40

                Rectangle {
                    id: customArrayContainer
                    width: 275
                    height: randomArrayLength.implicitHeight
                    border.color: Colors.getBorderColor()
                    opacity: fromArrayRadioButton.checked ? 1 : 0.5
                    color: Colors.getTextInputColor()
                    radius: 3

                    TextInput {
                        id: customArray
                        width: parent.width
                        padding: 2
                        clip: true
                        enabled: fromArrayRadioButton.checked
                        opacity: enabled ? 1 : 0.5
                        color:  Colors.getTextColor()
                    }
                }

                Text {
                    id: customArrayError
                    text: globals.language === "hu" ? "A bemenet egy maximum 15 hosszú, -999 és 999 közötti értékekből \nálló, vesszővel elválasztott lista legyen" : "Input must be at most 15 comma separated numbers from -999 to 999"
                    font.pixelSize: 10
                    color: "red"
                    opacity: 0
                }
            }
        }

        footer: RowLayout {
            Layout.alignment: Qt.AlignRight

            StyledButton {
                text: globals.language === "hu" ? "Létrehozás" : "Create"

                onClicked: {
                    if (fromArrayRadioButton.checked && !Utils.isValidArrayLiteral(customArray.text)) {
                        customArrayError.opacity = 1
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
}
