import QtQuick 2.15
import QtQuick.Shapes 1.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator

Item {
    property var editorModel: modelManager.createEditorPageModel(currentlyEditedTree.tree)
    property int maxSize: 15
    property int nodeSize: 40

    signal switchPage(string pageName)

    FocusScope {
        focus: true

        Keys.onPressed: {
            editorModel.setNodeKey
        }
    }

    Rectangle {
        id: editorContainer
        anchors.fill: parent
        anchors.margins: 10
        color: "#eeeeee"
        radius: 5

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
                    id: array
                    model: maxSize

                    delegate: Rectangle {
                        property var elementKey: elementKey

                        width: arrayContainer.width / maxSize
                        height: arrayContainer.width / maxSize
                        y: 5
                        color: nodes.itemAt(index)?.nodeKey.focus ? "#f07b32" : index % 2 === 0 ? "#bbb" : "#ccc"

                        Text {
                            id: elementKey
                            anchors.centerIn: parent

                            text: editorModel.tree[index] ?? ""
                            font.pixelSize: 18
                            color: nodes.itemAt(index)?.nodeKey.focus ? "white" : "black"
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
                        color: "white"
                        padding: 15

                        text: editorModel.tree[index]
                        font.pixelSize: 16

                        validator: IntValidator {
                            bottom: -999
                            top: 999
                        }

                        onTextChanged: {
                            currentlyEditedTree.tree[index] = Number(nodeKey.text)
                            if (array.itemAt(index)?.elementKey.text) {
                                array.itemAt(index).elementKey.text = Number(nodeKey.text)
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
                        currentlyEditedTree.addNode(1)
                        editorModel.addNode()
                    }
                }

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Remove Node")

                    onClicked: {
                        currentlyEditedTree.removeLastNode()
                        editorModel.removeNode()
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
                }

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Visualize ->")

                    onClicked: {
                        switchPage("Visualizer")
                    }
                }
            }
        }
    }
}
