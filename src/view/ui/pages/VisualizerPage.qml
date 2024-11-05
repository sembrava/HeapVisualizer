import QtQuick 2.15
import QtQuick.Shapes 1.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator
import "../logic/Animations.js" as Animations

Item {
    property var visualizerModel: modelManager.createVisualizerPageModel(globals.currentlyEditedTree, globals.currentAlgorithm, globals.documentHeapification)
    property int maxSize: 15
    property int nodeSize: 40

    signal switchPage(string pageName)

    Connections {
        target: visualizerModel

        function onNodesSwapped(greaterNodeIndex, smallerNodeIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, "#f07b32")) {
                    nodes.itemAt(i).color = "#888888"
                }
            }

            nodes.itemAt(greaterNodeIndex).color = "#f07b32"
            nodes.itemAt(smallerNodeIndex).color = "#f07b32"

            Animations.swapNodes(nodes, greaterNodeIndex, smallerNodeIndex)
        }

        function onNodesHighlighted(greaterNodeIndex, smallerNodeIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, "#f07b32")) {
                    nodes.itemAt(i).color = "#888888"
                }
            }

            nodes.itemAt(greaterNodeIndex).color = "#f07b32"
            nodes.itemAt(smallerNodeIndex).color = "#f07b32"
            nodes.itemAt(greaterNodeIndex).selectAnimation.start()
            nodes.itemAt(smallerNodeIndex).selectAnimation.start()
        }

        function onSortedBoundHighlighted(sortedBoundIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, "#f07b32")) {
                    nodes.itemAt(i).color = "#888888"
                }
            }

            nodes.itemAt(sortedBoundIndex).color = "#22bd5d"
            nodes.itemAt(sortedBoundIndex).selectAnimation.start()
        }

        function onSortedBoundReverted(sortedBoundIndex) {
            nodes.itemAt(sortedBoundIndex).color = "#888888";
        }

        function onVisualizationReset() {
            for (let i = 0; i < nodes.count; i++) {
                nodes.itemAt(i).color = "#888888"
            }

            extractedNode.visible = false
            extractedNode.x = PositionCalculator.calculateNodeXOffset(0, graphContainer.width, nodeSize)
            extractedNode.y = PositionCalculator.calculateNodeYOffset(0, 100, 50, nodeSize)

            stepBackwardButton.enabled = false
        }

        function onNodeExtracted(nodeKey) {
            for (let i = 0; i < nodes.count; i++) {
                nodes.itemAt(i).color = "#888888"
            }

            extractedNode.visible = false
            extractedNode.x = PositionCalculator.calculateNodeXOffset(0, graphContainer.width, nodeSize)
            extractedNode.y = PositionCalculator.calculateNodeYOffset(0, 100, 50, nodeSize)

            extractedNode.key = nodeKey
            extractedNode.visible = true
            extractionAnimation.start()
        }

        function onRootKeyChanged() {
            nodes.itemAt(0).color = "#f07b32"
            nodes.itemAt(0).selectAnimation.start()

            nodes.itemAt(visualizerModel.tree.length - 1).color = "#e33d3d"
            nodes.itemAt(visualizerModel.tree.length - 1).selectAnimation.start()
        }

        function onExplanationChanged(explanation) {
            explanationText.text = explanation
        }
    }

    Rectangle {
        id: editorContainer
        anchors.fill: parent
        anchors.margins: 10
        color: "#eeeeee"
        radius: 5

        Rectangle {
            id: arrayContainer
            width: parent.width
            height: 80
            anchors.top: parent.top
            color: "#dddddd"
            radius: 5

            Text {
                id: arrayLabel
                color: "#555555"
                x: 5
                y: 5

                text: qsTr("Array representation")
            }

            Row {
                anchors.bottom: arrayContainer.bottom

                Repeater {
                    model: maxSize

                    delegate: Rectangle {
                        width: arrayContainer.width / maxSize
                        height: arrayContainer.width / maxSize
                        y: 5
                        color: index % 2 === 0 ? "#bebebe" : "#cccccc"

                        Text {
                            anchors.centerIn: parent

                            text: visualizerModel.tree[index] ?? ""
                            font.pixelSize: 18
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

            Repeater {
                id: edges
                model: visualizerModel.tree.length - 1

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
                id: nodeBackgrounds
                model: visualizerModel.tree

                delegate: Rectangle {
                    width: nodeSize
                    height: nodeSize
                    radius: nodeSize / 2
                    x: PositionCalculator.calculateNodeXOffset(index, parent.width, nodeSize)
                    y: PositionCalculator.calculateNodeYOffset(index, 100, 50, nodeSize)
                    color: "#dddddd"
                }
            }

            Repeater {
                id: nodes
                model: visualizerModel.tree

                delegate: Rectangle {
                    property Animation swapAnimation: swapAnimation
                    property Animation selectAnimation: selectAnimation

                    width: nodeSize
                    height: nodeSize
                    radius: nodeSize / 2
                    x: PositionCalculator.calculateNodeXOffset(index, parent.width, nodeSize)
                    y: PositionCalculator.calculateNodeYOffset(index, 100, 50, nodeSize)
                    color: index >= visualizerModel.sortedBoundIndex ? "#22bd5d" : "#888888"

                    Text {
                        anchors.centerIn: parent
                        color: "white"

                        text: visualizerModel.tree[index]
                        font.pixelSize: 16
                    }

                    ParallelAnimation {
                        id: swapAnimation

                        SequentialAnimation {
                            ParallelAnimation {
                                NumberAnimation {
                                    target: nodes.itemAt(index)
                                    property: "x"
                                    to: 0
                                    duration: 250
                                    easing.type: Easing.InBack
                                }

                                NumberAnimation {
                                    target: nodes.itemAt(index)
                                    property: "y"
                                    to: 0
                                    duration: 250
                                    easing.type: Easing.InBack
                                }
                            }

                            ParallelAnimation {
                                NumberAnimation {
                                    target: nodes.itemAt(index)
                                    property: "x"
                                    to: nodes.itemAt(index).x
                                    duration: 250
                                    easing.type: Easing.OutBack
                                }

                                NumberAnimation {
                                    target: nodes.itemAt(index)
                                    property: "y"
                                    to: nodes.itemAt(index).y
                                    duration: 250
                                    easing.type: Easing.OutBack
                                }
                            }
                        }

                        SequentialAnimation {
                            NumberAnimation {
                                target: nodes.itemAt(index)
                                property: "scale"
                                to: 0.5
                                duration: 250
                            }

                            NumberAnimation {
                                target: nodes.itemAt(index)
                                property: "scale"
                                to: 1
                                duration: 250
                            }
                        }
                    }

                    ParallelAnimation {
                        id: selectAnimation

                        SequentialAnimation {
                            NumberAnimation {
                                target: nodes.itemAt(index)
                                property: "scale"
                                to: 0
                                duration: 0
                            }

                            NumberAnimation {
                                target: nodes.itemAt(index)
                                property: "scale"
                                to: 1
                                duration: 250
                                easing.type: Easing.OutBack
                            }
                        }
                    }
                }
            }

            Rectangle {
                property string key: ""

                id: extractedNode
                width: nodeSize
                height: nodeSize
                radius: nodeSize / 2
                x: PositionCalculator.calculateNodeXOffset(0, parent.width, nodeSize)
                y: PositionCalculator.calculateNodeYOffset(0, 100, 50, nodeSize)
                color: "blue"
                visible: false
                scale: 0

                Text {
                    id: extractedNodeKey
                    anchors.centerIn: parent
                    color: "white"

                    text: parent.key
                    font.pixelSize: 16
                }

                ParallelAnimation {
                    id: extractionAnimation

                    NumberAnimation {
                        target: extractedNode
                        property: "x"
                        to: parent.width - nodeSize - 70
                        duration: 300
                        easing.type: Easing.OutBack
                    }

                    NumberAnimation {
                        target: extractedNode
                        property: "y"
                        to: 50
                        duration: 300
                        easing.type: Easing.OutBack
                    }

                    NumberAnimation {
                        target: extractedNode
                        property: "scale"
                        to: 1
                        duration: 300
                        easing.type: Easing.OutBack
                    }
                }
            }

            Text {
                id: explanationText
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                font.pixelSize: 15
                color: "#333"

                onTextChanged: {
                    textChangedAnimation.start()
                }

                SequentialAnimation {
                    id: textChangedAnimation

                    NumberAnimation {
                        target: explanationText
                        property: "scale"
                        to: 0.75
                        duration: 0
                    }

                    NumberAnimation {
                        target: explanationText
                        property: "scale"
                        to: 1
                        duration: 250
                        easing.type: Easing.OutBack
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

            HoverButton {
                anchors.verticalCenter: parent.verticalCenter
                width: 150
                height: 35
                text: qsTr("Back")

                onClicked: {
                    switchPage("Editor")
                }
            }

            Column {
                anchors.centerIn: parent
                width: 300
                height: parent.height

                Row {
                    HoverButton {
                        id: stepBackwardButton
                        text: "<"
                        enabled: false

                        onClicked: {
                            visualizerModel.stepBackward()
                        }
                    }

                    HoverButton {
                        text: "Auto"
                    }

                    HoverButton {
                        id: stepForwardButton
                        text: ">"

                        onClicked: {
                            stepBackwardButton.enabled = true

                            visualizerModel.stepForward()
                        }
                    }
                }
            }
        }
    }
}
