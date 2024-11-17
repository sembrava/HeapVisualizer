import QtQuick 2.15
import QtQuick.Controls 2.15
import "../general"
import "../logic/Colors.js" as Colors

Item {
    property var settingsModel: modelManager.createSettingsPageModel()

    signal switchPage(string pageName)

    Column {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        Section {
            content: Text {
                color: Colors.getTextColor()
                font.bold: true
                font.pixelSize: 18
                text: globals.language === "hu" ? "Nyelv" : "Language"
            }
        }

        Section {
            content: Column {
                StyledRadioButton {
                    text: "English"
                    checked: globals.language === "en"

                    onCheckedChanged: {
                        if (checked && globals.language !== "en")
                            settingsModel.setLanguage("en");
                    }
                }

                StyledRadioButton {
                    text: "Magyar"
                    checked: globals.language === "hu"

                    onCheckedChanged: {
                        if (checked && globals.language !== "hu")
                            settingsModel.setLanguage("hu")
                    }
                }
            }
        }

        Section {
            content: Text {
                color: Colors.getTextColor()
                font.bold: true
                font.pixelSize: 18
                text: globals.language === "hu" ? "Téma" : "Theme"
            }
        }

        Section {
            content: Column {
                StyledRadioButton {
                    text: globals.language === "hu" ? "Világos" : "Light"
                    checked: globals.isLightTheme

                    onCheckedChanged: {
                        if (checked && globals.isLightTheme !== checked)
                            settingsModel.setTheme("light")
                    }
                }

                StyledRadioButton {
                    text: globals.language === "hu" ? "Sötét" : "Dark"
                    checked: !globals.isLightTheme

                    onCheckedChanged: {
                        if (checked && globals.isLightTheme === checked)
                            settingsModel.setTheme("dark")
                    }
                }
            }
        }
    }
}
