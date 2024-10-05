import QtQuick 2.15
import QtQuick.Shapes 1.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator
import "../logic/Animations.js" as Animations

Item {
    property var visualizerModel: modelManager.createVisualizerPageModel(currentlyEditedTree.tree)
    property int maxSize: 15
    property int nodeSize: 40

    signal switchPage(string pageName)

    Connections {
        target: visualizerModel

        function onNodesSwapped(greaterNodeIndex, smallerNodeIndex) {
            const tempIndex = visualizerModel.tree[smallerNodeIndex]
            visualizerModel.setNodeKey(smallerNodeIndex, visualizerModel.tree[greaterNodeIndex])
            visualizerModel.setNodeKey(greaterNodeIndex, tempIndex)

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

            nodes.itemAt(greaterNodeIndex).selectAnimation.start()
            nodes.itemAt(smallerNodeIndex).selectAnimation.start()
        }

        function onSortedBoundHighlighted(sortedBoundIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, "#f07b32")) {
                    nodes.itemAt(i).color = "#888888"
                }
            }

            nodes.itemAt(sortedBoundIndex).sortedBoundAnimation.start()
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
                    property Animation sortedBoundAnimation: sortedBoundAnimation

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

                        ColorAnimation {
                            target: nodes.itemAt(index)
                            property: "color"
                            to: "#f07b32"
                            duration: 0
                        }
                    }

                    ParallelAnimation {
                        id: sortedBoundAnimation

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

                        ColorAnimation {
                            target: nodes.itemAt(index)
                            property: "color"
                            to: "#22bd5d"
                            duration: 0
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
                        text: "<"
                    }

                    HoverButton {
                        text: "Auto"
                    }

                    HoverButton {
                        text: ">"

                        onClicked: {
                            visualizerModel.stepForward()
                        }
                    }
                }
            }
        }
    }
}
