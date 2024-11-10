import QtQuick 2.15
import QtQuick.Shapes 1.15
import QtQuick.Controls 2.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator
import "../logic/Utils.js" as Utils

Item {
    property var editorModel: modelManager.createEditorPageModel(globals.currentlyEditedTree)
    property int maxSize: 15
    property int nodeSize: 40

    signal switchPage(string pageName)

    Rectangle {
        id: editorContainer
        anchors.fill: parent
        anchors.margins: 10
        color: "#eeeeee"
        radius: 5
        clip: true

        MouseArea {
            anchors.fill: parent

            onClicked: {
                for (let i = 0; i < nodes.count; i++) {
                    nodes.itemAt(i).nodeKey.focus = false
                }
            }
        }

        Rectangle {
            id: arrayContainer
            width: parent.width
            height: 80
            anchors.top: parent.top
            color: "#dddddd"

            Text {
                id: arrayLabel
                color: "#555555"
                x: 5
                y: 5

                text: qsTr("Array representation")
            }

            Row {
                anchors.bottom: arrayContainer.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 7

                Repeater {
                    id: array
                    model: maxSize

                    delegate: Rectangle {
                        property var elementKey: elementKey

                        width: 50
                        height: width
                        y: 5
                        radius: 5
                        color: "#bbb"

                        Text {
                            id: elementKey
                            anchors.centerIn: parent

                            text: editorModel.tree[index] ?? ""
                            font.pixelSize: 18
                            color: "black"
                        }

                        Text {
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottomMargin: 1

                            text: index
                            font.pixelSize: 10
                            color: "#666"
                        }
                    }
                }
            }
        }

        Rectangle {
            id: graphContainer
            width: parent.width
            anchors.top: arrayContainer.bottom
            anchors.bottom: controlPanel.top
            color: "#eeeeee"

            Text {
                color: "#555555"
                x: 5
                y: 5

                text: qsTr("Graph representation")
            }

            Text {
                color: "#555555"
                anchors.right: parent.right
                anchors.rightMargin: 5
                y: 5

                text: qsTr("Click on a node to edit its value")
            }

            Repeater {
                model: editorModel.tree.length - 1

                delegate: Shape {
                    id: start
                    x: PositionCalculator.calculateEdgeStartXOffset(index + 1, parent.width, nodeSize)
                    y: PositionCalculator.calculateEdgeStartYOffset(index + 1, 100, 50, nodeSize)

                    ShapePath {
                        strokeColor: "#cccccc"
                        strokeWidth: 1

                        PathLine {
                            x: PositionCalculator.calculateEdgeEndXOffset(index + 1, parent.width, nodeSize) - start.x
                            y: PositionCalculator.calculateEdgeEndYOffset(index + 1, 100, 50) - start.y
                        }
                    }
                }
            }

            Repeater {
                id: nodes
                model: editorModel.tree

                delegate: Rectangle {
                    property var nodeKey: nodeKey

                    width: nodeSize
                    height: nodeSize
                    radius: nodeSize / 2
                    x: PositionCalculator.calculateNodeXOffset(index, parent.width, nodeSize)
                    y: PositionCalculator.calculateNodeYOffset(index, 100, 50)
                    color: nodeKey.focus ? "#f07b32" : "#888"

                    TextInput {
                        id: nodeKey
                        anchors.centerIn: parent
                        padding: 15
                        focus: editorModel.currentlySelectedNodeIndex === index
                        color: "white"

                        text: editorModel.tree[index]
                        font.pixelSize: 16

                        validator: IntValidator {
                            bottom: -999
                            top: 999
                        }

                        onTextChanged: {
                            if (text.startsWith("0"))
                                text = text.replace(/^0+(?!$)/, '')

                            if (text.length === 0)
                                text = "0"

                            if (array.itemAt(index))
                                array.itemAt(index).elementKey.text = text
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.IBeamCursor

                            onClicked: {
                                parent.forceActiveFocus()
                                parent.cursorPosition = parent.text.length
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: controlPanel
            width: parent.width
            height: 100
            anchors.bottom: parent.bottom
            color: "#dddddd"
            radius: 5

            Row {
                anchors.verticalCenter: parent.verticalCenter

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length < maxSize
                    text: qsTr("Add Node")

                    onClicked: {
                        syncTree()
                        editorModel.addNode()
                    }
                }

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Remove Node")

                    onClicked: {
                        syncTree()
                        editorModel.removeNode()

                        for (let i = 0; i < maxSize; i++) {
                            array.itemAt(i).elementKey.text = editorModel.tree[i] ?? ""
                        }
                    }
                }
            }

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Save")

                    onClicked: {
                        syncTree()
                        saveVisualizationPopup.open()
                    }
                }

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Visualize ->")

                    onClicked: {
                        syncTree()
                        algorithmSelector.open()
                    }
                }
            }
        }
    }

    Popup {
        id: algorithmSelector
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
            text: qsTr("Choose algorithm")
        }

        HoverButton {
            anchors.right: parent.right
            text: "x"

            onClicked: {
                algorithmSelector.close()
            }
        }

        Column {
            anchors.topMargin: 10
            anchors.top: popupTitle.bottom
            spacing: 10

            RadioButton {
                id: heapSortRadioButton
                text: qsTr("Heap sort")
                checked: true
            }

            RadioButton {
                id: removeMaxRadioButton
                text: qsTr("Remove max")
            }

            RadioButton {
                id: insertNodeRadioButton
                text: qsTr("Insert node")
                enabled: editorModel.tree.length < 15
            }

            Row {
                x: 20
                spacing: 10

                Text {
                    text: qsTr("Key")
                    color: insertNodeRadioButton.checked ? "#000" : "#ccc"
                }

                Rectangle {
                    anchors.leftMargin: 10
                    width: 50
                    height: newNodeKey.implicitHeight
                    border.color: insertNodeRadioButton.checked ? "#ccc" : "#eee"
                    radius: 3

                    TextInput {
                        id: newNodeKey
                        width: parent.width
                        padding: 2
                        enabled: insertNodeRadioButton.checked
                        color: insertNodeRadioButton.checked ? "#000" : "#ccc"

                        validator: IntValidator {
                            bottom: -999
                            top: 999
                        }
                    }
                }
            }
        }

        HoverButton {
            id: startButton
            text: qsTr("Start")
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                if (heapSortRadioButton.checked) {
                    globals.currentAlgorithm = "heapSort"
                    switchPage("Visualizer")
                }

                else if (removeMaxRadioButton.checked) {
                    globals.currentAlgorithm = "removeMax"

                    if (!Utils.isMaxHeap(globals.currentlyEditedTree)) {
                        heapifyPopup.open()
                    }

                    else {
                        switchPage("Visualizer")
                    }
                }

                else if (insertNodeRadioButton.checked) {
                    globals.newNodeKey = Number(newNodeKey.text)
                    globals.currentAlgorithm = "insertNode"

                    if (!Utils.isMaxHeap(globals.currentlyEditedTree)) {
                        heapifyPopup.open()
                    }

                    else {
                        switchPage("Visualizer")
                    }
                }
            }
        }

        CheckBox {
            id: skipHeapificationCheckbox
            text: qsTr("Skip heapification")
            anchors.right: startButton.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            enabled: heapSortRadioButton.checked

            onCheckedChanged: {
                globals.documentHeapification = !skipHeapificationCheckbox.checked
            }
        }
    }

    Popup {
        id: saveVisualizationPopup
        width: 350
        height: 100
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true

        background: Rectangle {
            color: "white"
            border.color: "#bbb"
            radius: 5
        }

        Text {
            id: saveVisualizationTitle
            text: qsTr("Save visualization")
        }

        HoverButton {
            anchors.right: parent.right
            text: "x"

            onClicked: {
                saveVisualizationPopup.close()
            }
        }

        Column {
            anchors.top: saveVisualizationTitle.bottom
            anchors.topMargin: 10
            spacing: 5

            Text {
                text: qsTr("Save as")
            }

            Rectangle {
                anchors.leftMargin: 10
                width: 200
                height: fileName.implicitHeight
                border.color: "#ccc"
                radius: 3

                TextInput {
                    id: fileName
                    width: parent.width
                    padding: 2
                    color: "#000"
                    text: globals.currentFileName
                    focus: true

                    Component.onCompleted: {
                        fileName.selectAll()
                    }
                }
            }
        }

        HoverButton {
            text: qsTr("Save")
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                editorModel.saveVisualization(fileName.text, globals.currentlyEditedTree)

                saveVisualizationPopup.close()
            }
        }
    }

    Popup {
        id: heapifyPopup
        width: 450
        height: 100
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true

        background: Rectangle {
            color: "white"
            border.color: "#bbb"
            radius: 5
        }

        Text {
            id: heapifyTitle
            text: qsTr("Alert")
        }

        HoverButton {
            anchors.right: parent.right
            text: "x"

            onClicked: {
                heapifyPopup.close()
            }
        }

        Column {
            anchors.top: heapifyTitle.bottom
            anchors.topMargin: 10
            spacing: 5

            Text {
                width: parent.width
                wrapMode: Text.WordWrap
                text: qsTr("The provided array does not satisfy the heap property.\nWould you like to run the algorithm on a heapified version of the array?")
            }
        }

        HoverButton {
            id: yesButton
            text: qsTr("Yes")
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked: {
                nodes.model = null
                Utils.heapify(globals.currentlyEditedTree)
                switchPage("Visualizer")
            }
        }

        HoverButton {
            id: noButton
            text: qsTr("No")
            anchors.right: yesButton.left
            anchors.bottom: parent.bottom

            onClicked: {
                heapifyPopup.close()
            }
        }
    }

    function syncTree() {
        const temp = []

        for (let i = 0; i < editorModel.tree.length; i++) {
            temp.push(Number(nodes.itemAt(i).nodeKey.text))
        }

        for (let j = 0; j < temp.length; j++) {
            editorModel.setNodeKey(j, temp[j])
        }

        globals.currentlyEditedTree = temp
    }
}
