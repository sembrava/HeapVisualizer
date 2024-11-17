import QtQuick 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 2.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator
import "../logic/Animations.js" as Animations
import "../logic/Colors.js" as Colors

Item {
    property var visualizerModel: modelManager.createVisualizerPageModel(globals.currentlyEditedTree, globals.currentAlgorithm, globals.documentHeapification, globals.newNodeKey)
    property int maxSize: 15
    property int nodeSize: 40
    property int graphYOffset: 30

    signal switchPage(string pageName)

    Connections {
        target: visualizerModel

        function onNodesSwapped(greaterNodeIndex, smallerNodeIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    nodes.itemAt(i).color = Colors.getElementColor(i)
                }

                if (Qt.colorEqual(array.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    array.itemAt(i).color = Colors.getElementColor(i)
                }
            }

            nodes.itemAt(greaterNodeIndex).color = Colors.getSelectedNodeColor()
            nodes.itemAt(smallerNodeIndex).color = Colors.getSelectedNodeColor()
            array.itemAt(greaterNodeIndex).color = Colors.getSelectedNodeColor()
            array.itemAt(smallerNodeIndex).color = Colors.getSelectedNodeColor()

            Animations.swapNodes(nodes, greaterNodeIndex, smallerNodeIndex)
        }

        function onNodesHighlighted(greaterNodeIndex, smallerNodeIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    nodes.itemAt(i).color = Colors.getElementColor(i)
                }

                if (Qt.colorEqual(array.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    array.itemAt(i).color = Colors.getElementColor(i)
                }
            }

            nodes.itemAt(greaterNodeIndex).color = Colors.getSelectedNodeColor()
            nodes.itemAt(smallerNodeIndex).color = Colors.getSelectedNodeColor()
            array.itemAt(greaterNodeIndex).color = Colors.getSelectedNodeColor()
            array.itemAt(smallerNodeIndex).color = Colors.getSelectedNodeColor()

            nodes.itemAt(greaterNodeIndex).selectAnimation.start()
            nodes.itemAt(smallerNodeIndex).selectAnimation.start()
        }

        function onSortedBoundHighlighted(sortedBoundIndex) {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    nodes.itemAt(i).color = Colors.getElementColor(i)
                }

                if (Qt.colorEqual(array.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    array.itemAt(i).color = Colors.getElementColor(i)
                }
            }

            nodes.itemAt(sortedBoundIndex).color = Colors.getSortedNodeColor()
            array.itemAt(sortedBoundIndex).color = Colors.getSortedNodeColor()

            nodes.itemAt(sortedBoundIndex).selectAnimation.start()
        }

        function onSortedBoundReverted(sortedBoundIndex) {
            nodes.itemAt(sortedBoundIndex).color = Colors.getElementColor(sortedBoundIndex)
            array.itemAt(sortedBoundIndex).color = Colors.getElementColor(sortedBoundIndex)
        }

        function onVisualizationReset() {
            for (let i = 0; i < maxSize; i++) {
                if (nodes.itemAt(i))
                    nodes.itemAt(i).color = Colors.getElementColor(i)

                if (array.itemAt(i))
                    array.itemAt(i).color = Colors.getElementColor(i)
            }

            extractedNode.visible = false
            extractedNode.x = PositionCalculator.calculateNodeXOffset(0, graphContainer.width, nodeSize)
            extractedNode.y = PositionCalculator.calculateNodeYOffset(0, 100, graphYOffset, nodeSize)

            stepBackwardButton.enabled = false
        }

        function onVisualizationFinished() {
            for (let i = 0; i < nodes.count; i++) {
                if (Qt.colorEqual(nodes.itemAt(i).color, Colors.getSelectedNodeColor())) {
                    nodes.itemAt(i).color = Colors.getElementColor(i)
                    array.itemAt(i).color = Colors.getElementColor(i)
                }
            }

            stepForwardButton.enabled = false
        }

        function onNodeExtracted(nodeKey) {
            for (let i = 0; i < nodes.count; i++) {
                nodes.itemAt(i).color = Colors.getElementColor(i)
                array.itemAt(i).color = Colors.getElementColor(i)
            }

            extractedNode.visible = false
            extractedNode.x = PositionCalculator.calculateNodeXOffset(0, graphContainer.width, nodeSize)
            extractedNode.y = PositionCalculator.calculateNodeYOffset(0, 100, graphYOffset, nodeSize)

            extractedNode.key = nodeKey
            extractedNode.visible = true
            extractionAnimation.start()
        }

        function onRootKeyChanged() {
            nodes.itemAt(0).color = Colors.getSelectedNodeColor()
            array.itemAt(0).color = Colors.getSelectedNodeColor()

            nodes.itemAt(0).selectAnimation.start()

            nodes.itemAt(visualizerModel.tree.length - 1).color = Colors.getSecondarySelectedNodeColor()
            array.itemAt(visualizerModel.tree.length - 1).color = Colors.getSecondarySelectedNodeColor()

            nodes.itemAt(visualizerModel.tree.length - 1).selectAnimation.start()
        }

        function onNodeRemoved() {
            array.itemAt(visualizerModel.tree.length).color = Colors.getElementColor(visualizerModel.tree.length)
        }

        function onNodeAdded() {
            nodes.itemAt(visualizerModel.tree.length - 1).color = Colors.getSelectedNodeColor()
            array.itemAt(visualizerModel.tree.length - 1).color = Colors.getSelectedNodeColor()

            nodes.itemAt(visualizerModel.tree.length - 1).selectAnimation.start()
        }

        function onExplanationChanged(explanation) {
            explanationText.text = explanation
        }
    }

    Column {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        Section {
            Column {
                id: arrayContainer
                width: parent.width
                height: 80

                Text {
                    id: arrayLabel
                    color: Colors.getTextColor()
                    opacity: 0.7

                    text: globals.language === "hu" ? "Tömbös nézet" : "Array representation"
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 7

                    Repeater {
                        id: array
                        model: maxSize

                        delegate: Rectangle {
                            width: 50
                            height: width
                            y: 5
                            radius: 5
                            color: Colors.getElementColor(index)
                            border.color: Colors.getBorderColor()
                            border.width: 1
                            opacity: index < visualizerModel.tree.length ? 1 : 0.5

                            Text {
                                anchors.centerIn: parent

                                text: visualizerModel.tree[index] ?? ""
                                font.pixelSize: 18
                                color: Colors.getNodeKeyColor()
                            }

                            Text {
                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottomMargin: 1

                                text: index < visualizerModel.tree.length ? index : ""
                                font.pixelSize: 10
                                color: Colors.getIndexColor()
                            }
                        }
                    }
                }
            }
        }

        Section {
            Rectangle {
                id: graphContainer
                width: parent.width
                height: 415
                color: "transparent"

                Text {
                    color: Colors.getTextColor()
                    opacity: 0.7
                    text: globals.language === "hu" ? "Gráfos nézet" : "Graph representation"
                }

                Repeater {
                    id: edges
                    model: visualizerModel.tree.length === 0 ? 0 : visualizerModel.tree.length - 1

                    delegate: Shape {
                        id: start
                        x: PositionCalculator.calculateEdgeStartXOffset(index + 1, parent.width, nodeSize)
                        y: PositionCalculator.calculateEdgeStartYOffset(index + 1, 100, graphYOffset, nodeSize)
                        opacity: globals.isLightTheme ? 0.6 : 0.4

                        ShapePath {
                            strokeColor: Colors.getBorderColor()
                            strokeWidth: 1

                            PathLine {
                                x: PositionCalculator.calculateEdgeEndXOffset(index + 1, parent.width, nodeSize) - start.x
                                y: PositionCalculator.calculateEdgeEndYOffset(index + 1, 100, graphYOffset) - start.y
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
                        y: PositionCalculator.calculateNodeYOffset(index, 100, graphYOffset, nodeSize)
                        color: Colors.getNodeBackgroundColor()
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
                        y: PositionCalculator.calculateNodeYOffset(index, 100, graphYOffset, nodeSize)
                        color: index >= visualizerModel.sortedBoundIndex ? Colors.getSortedNodeColor() : Colors.getElementColor(index)
                        border.color: Colors.getBorderColor()
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            color: Colors.getNodeKeyColor()

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
                    y: PositionCalculator.calculateNodeYOffset(0, 100, graphYOffset, nodeSize)
                    color: Colors.getExtractedNodeColor()
                    visible: false
                    scale: 0
                    border.color: Colors.getBorderColor()
                    border.width: 1

                    Text {
                        id: extractedNodeKey
                        anchors.centerIn: parent
                        color: "#fff"

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
                            to: graphYOffset
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
                    color: Colors.getTextColor()
                    opacity: 0.7

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
        }

        Section {
            id: controlPanel
            height: backButton.height + 20

            Rectangle {
                anchors.fill: parent
                color: "transparent"

                StyledButton {
                    id: backButton
                    anchors.verticalCenter: parent.verticalCenter
                    text: globals.language === "hu" ? "Vissza" : "Back"

                    onClicked: {
                        switchPage("Editor")
                    }
                }

                RowLayout {
                    anchors.centerIn: parent

                    StyledButton {
                        id: stepBackwardButton
                        text: "<"
                        bold: true
                        enabled: false

                        onClicked: {
                            stepForwardButton.enabled = true

                            visualizerModel.stepBackward()
                        }
                    }

                    StyledButton {
                        id: stepForwardButton
                        text: ">"
                        bold: true

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
