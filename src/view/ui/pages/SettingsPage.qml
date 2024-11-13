import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var settingsModel: modelManager.createSettingsPageModel()

    signal switchPage(string pageName)

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        Text {
            text: globals.language === "hu" ? "Nyelv" : "Language"
        }

        Column {
            RadioButton {
                text: "English"
                checked: globals.language === "en"

                onCheckedChanged: {
                    if (checked && globals.language !== "en")
                        settingsModel.setLanguage("en");
                }
            }

            RadioButton {
                text: "Magyar"
                checked: globals.language === "hu"

                onCheckedChanged: {
                    if (checked && globals.language !== "hu")
                        settingsModel.setLanguage("hu")
                }
            }
        }

        Text {
            text: globals.language === "hu" ? "Téma" : "Theme"
        }

        Column {
            RadioButton {
                text: globals.language === "hu" ? "Világos" : "Light"
                checked: globals.isLightTheme

                onCheckedChanged: {
                    if (checked && globals.isLightTheme !== checked)
                        settingsModel.setTheme("light")
                }
            }

            RadioButton {
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
