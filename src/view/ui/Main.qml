import QtQuick 2.15
import QtQuick.Controls 2.15
import "general"

Window {
    id: window
    width: 960
    height: 640
    maximumWidth: width
    minimumWidth: width
    maximumHeight: height
    minimumHeight: height
    visible: true
    title: "HeapVisualizer"

    Row {
        anchors.fill: parent

        Rectangle {
            id: sidebarContainer
            width: 75
            height: parent.height
            color: "#eeeeee"

            Column {
                anchors.centerIn: parent
                spacing: 10

                HoverButton {
                    id: homeButton
                    width: 60
                    text: qsTr("Home")
                    enabled: true

                    onClicked: {
                        onPageSwitched("Home")
                    }
                }

                HoverButton {
                    id: editorButton
                    width: 60
                    text: qsTr("Editor")
                    enabled: false

                    onClicked: {
                        onPageSwitched("Editor")
                    }
                }

                HoverButton {
                    id: visualizerButton
                    width: 60
                    text: qsTr("Visualizer")
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
        switch (pageName) {
            case "Home":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/HomePage.qml"

                homeButton.enabled = false
                editorButton.enabled = false
                visualizerButton.enabled = false

                break

            case "Editor":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/EditorPage.qml"

                homeButton.enabled = true
                editorButton.enabled = false
                visualizerButton.enabled = false

                break

            case "Visualizer":
                pageLoader.source = "qrc:/HeapVisualizer/src/view/ui/pages/VisualizerPage.qml"

                homeButton.enabled = true
                editorButton.enabled = true
                visualizerButton.enabled = false

                break

            default:
                console.log("Something went wrong")

                break
        }
    }
}

