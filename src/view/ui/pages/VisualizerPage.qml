import QtQuick 2.15

Item {
    property var visualizerModel: modelManager.createVisualizerPageModel()

    signal switchPage(string pageName)

    Text {
        text: "This is the Visualizer page"
    }
}
