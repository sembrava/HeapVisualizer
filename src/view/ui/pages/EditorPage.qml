import QtQuick 2.15
import QtQuick.Shapes 1.15
import "../general"

Item {
    property var editorModel: modelManager.createEditorPageModel()
    property int maxSize: 15
    property int nodeSize: 40

    signal switchPage(string pageName)

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
                        color: index % 2 === 0 ? "#bbbbbb" : "#aaaaaa"

                        Text {
                            anchors.centerIn: parent

                            text: editorModel.tree[index] ?? ""
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
                model: editorModel.tree

                delegate: Rectangle {
                    property bool isActive: false

                    width: nodeSize
                    height: nodeSize
                    radius: nodeSize / 2
                    x: calculateXOffset(index, parent.width, nodeSize)
                    y: calculateYOffset(index, 100, 50)
                    color: "#888888"

                    Text {
                        anchors.centerIn: parent
                        color: "white"

                        text: editorModel.tree[index]
                        font.pixelSize: 16
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                            if (!isActive) {
                                editorModel.selectNode(index)
                            }

                            parent.color = isActive ? "#888888" : "red"
                            isActive = !isActive
                        }
                    }
                }
            }

            Repeater {
                model: editorModel.tree.length

                delegate: Shape {
                    id: start
                    x: calculateStartXOffset(index, parent.width, nodeSize)
                    y: calculateStartYOffset(index, 100, 50)

                    ShapePath {
                        strokeColor: "#cccccc"
                        strokeWidth: 1

                        PathLine {
                            x: calculateEndXOffset(index, parent.width, nodeSize) - start.x
                            y: calculateEndYOffset(index, 100, 50) - start.y
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
                        editorModel.addNode()
                    }
                }

                HoverButton {
                    width: 150
                    height: 35
                    enabled: editorModel.tree.length > 0
                    text: qsTr("Remove Node")

                    onClicked: {
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
                    text: qsTr("Visualize")

                    onClicked: {
                        switchPage("Visualizer")
                    }
                }
            }
        }
    }

    function getLevel(index) {
        return Math.floor(Math.log2(index + 1));
    }

    function getNodeCountByLevel(level) {
        return Math.pow(2, level)
    }

    function getNodePositionWithinLevel(index, level) {
        return index - (Math.pow(2, level) - 1) + 1
    }

    function calculateXOffset(index, totalWidth, nodeSize) {
        const level = getLevel(index)
        const nodeCount = getNodeCountByLevel(level)
        const spaceTakenUpByNodes = nodeCount * nodeSize
        const spaceBetweenNodes = (totalWidth - spaceTakenUpByNodes) / (nodeCount + 1)
        const positionWithinLevel = getNodePositionWithinLevel(index, level)

        return positionWithinLevel * nodeSize + positionWithinLevel * spaceBetweenNodes - nodeSize
    }

    function calculateYOffset(index, paddingBetweenLevels, topPadding) {
        return getLevel(index) * paddingBetweenLevels + topPadding
    }

    function calculateStartXOffset(index, totalWidth, nodeSize) {
        return calculateXOffset(getParent(index), totalWidth, nodeSize) + nodeSize / 2
    }

    function calculateStartYOffset(index, paddingBetweenLevels, topPadding) {
        return calculateYOffset(getParent(index), paddingBetweenLevels, topPadding) + nodeSize
    }

    function calculateEndXOffset(index, totalWidth, nodeSize) {
        return calculateXOffset(index, totalWidth, nodeSize) + nodeSize / 2
    }

    function calculateEndYOffset(index, paddingBetweenLevels, topPadding) {
        return calculateYOffset(index, paddingBetweenLevels, topPadding)
    }

    function getParent(index) {
        return Math.floor((index - 1) / 2)
    }
}
