import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    signal switchPage(string pageName)

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        Text {
            text: globals.language === "hu" ? "Nyelv" : "Language"
        }

        RadioButton {
            text: "English"
            checked: globals.language === "en"

            onCheckedChanged: {
                if (checked && globals.language !== "en")
                    globals.language = "en"
            }
        }

        RadioButton {
            text: "Magyar"
            checked: globals.language === "hu"

            onCheckedChanged: {
                if (checked && globals.language !== "hu")
                    globals.language = "hu"
            }
        }

        Text {
            text: globals.language === "hu" ? "Téma" : "Theme"
        }

        RadioButton {
            text: globals.language === "hu" ? "Rendszer" : "System"
        }

        RadioButton {
            text: globals.language === "hu" ? "Világos" : "Light"
        }

        RadioButton {
            text: globals.language === "hu" ? "Sötét" : "Dark"
        }
    }
}
