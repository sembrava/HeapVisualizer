import QtQuick 2.15
import QtQuick.Controls 2.15
import "general"
import "logic/Colors.js" as Colors

Window {
    id: window
    width: 960
    height: 640
    maximumWidth: width
    minimumWidth: width
    maximumHeight: height
    minimumHeight: height
    visible: true
    title: (globals.currentFileName.length > 0 ? globals.currentFileName + " - " : "") + "HeapVisualizer"
    color: Colors.getBackgroundColor()
    Material.theme: globals.isLightTheme ? Material.Light : Material.Dark

    Row {
        anchors.fill: parent

        Rectangle {
            id: sidebarContainer
            width: 80
            height: parent.height
            color: Colors.getSectionColor()

            Column {
                anchors.centerIn: parent
                spacing: 10

                SidebarButton {
                    id: homeButton
                    source: "qrc:/HeapVisualizer/resources/icons/home-icon.svg"
                    title: globals.language === "hu" ? "Főoldal" : "Home"
                    enabled: false
                    selected: true

                    onClicked: {
                        onPageSwitched("Home")
                    }
                }

                SidebarButton {
                    id: editorButton
                    source: "qrc:/HeapVisualizer/resources/icons/editor-icon.svg"
                    title: globals.language === "hu" ? "Szerkesztő" : "Editor"
                    enabled: true

                    onClicked: {
                        onPageSwitched("Editor")
                    }
                }

                SidebarButton {
                    id: visualizerButton
                    source: "qrc:/HeapVisualizer/resources/icons/visualizer-icon.svg"
                    title: globals.language === "hu" ? "Szemléltetés" : "Visualizer"
                    enabled: false

                    onClicked: {
                        onPageSwitched("Visualizer")
                    }
                }
            }
        }

        Loader {
            id: pageLoader
            width: parent.width - sidebarContainer.width
            height: parent.height
            source: "qrc:/HeapVisualizer/src/view/ui/pages/HomePage.qml"

            onLoaded: {
                if (pageLoader.item) {
                    pageLoader.item.switchPage.connect(onPageSwitched)
                }
            }
        }
    }

    function onPageSwitched(pageName, tree) {
        pageLoader.source = ""

        switch (pageName) {
            case "Home":
                globals.currentFileName = ""
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/HomePage.qml"

                homeButton.enabled = false
                homeButton.selected = true
                editorButton.enabled = true
                editorButton.selected = false
                visualizerButton.enabled = false
                visualizerButton.selected = false

                break

            case "Editor":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/EditorPage.qml"

                homeButton.enabled = true
                homeButton.selected = false
                editorButton.enabled = false
                editorButton.selected = true
                visualizerButton.enabled = false
                visualizerButton.selected = false

                break

            case "Visualizer":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/VisualizerPage.qml"

                homeButton.enabled = true
                homeButton.selected = false
                editorButton.enabled = true
                editorButton.selected = false
                visualizerButton.enabled = false
                visualizerButton.selected = true

                break

            case "Settings":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/SettingsPage.qml"

                homeButton.enabled = true
                homeButton.selected = false
                editorButton.enabled = true
                editorButton.selected = false
                visualizerButton.enabled = false
                visualizerButton.selected = false

                break;

            default:
                console.log("Something went wrong")

                break
        }
    }
}

