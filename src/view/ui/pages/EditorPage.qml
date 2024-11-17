import QtQuick 2.15
import QtQuick.Shapes 1.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../general"
import "../logic/PositionCalculator.js" as PositionCalculator
import "../logic/Utils.js" as Utils
import "../logic/Colors.js" as Colors

Item {
    property var editorModel: modelManager.createEditorPageModel(globals.currentlyEditedTree)
    property int maxSize: 15
    property int nodeSize: 40
    property int graphYOffset: 30

    signal switchPage(string pageName)

    id: editorPageContainer

    MouseArea {
        anchors.fill: parent

        onClicked: {
            for (let i = 0; i < maxSize; i++) {
                if (nodes.itemAt(i))
                    nodes.itemAt(i).nodeKey.focus = false

                array.itemAt(i).color = Colors.getElementColor(i)
            }
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
                            property var elementKey: elementKey

                            width: 50
                            height: width
                            y: 5
                            radius: 5
                            color: nodes.itemAt(index)?.nodeKey.focus ? Colors.getSelectedNodeColor() : Colors.getElementColor(index)
                            border.color: Colors.getBorderColor()
                            border.width: 1
                            opacity: index < editorModel.tree.length ? 1 : 0.5

                            Text {
                                id: elementKey
                                anchors.centerIn: parent

                                text: editorModel.tree[index] ?? ""
                                font.pixelSize: 18
                                color: Colors.getNodeKeyColor()
                            }

                            Text {
                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottomMargin: 1

                                text: index < editorModel.tree.length ? index : ""
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

                Text {
                    color: Colors.getTextColor()
                    opacity: 0.7
                    anchors.right: parent.right
                    anchors.rightMargin: 5

                    text: globals.language === "hu" ? "Kattints egy cúcsra az értéke módosításához" : "Click on a node to edit its value"
                }

                Repeater {
                    model: editorModel.tree.length === 0 ? 0 : editorModel.tree.length - 1

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
                    id: nodes
                    model: editorModel.tree

                    delegate: Rectangle {
                        property var nodeKey: nodeKey

                        width: nodeSize
                        height: nodeSize
                        radius: nodeSize / 2
                        x: PositionCalculator.calculateNodeXOffset(index, parent.width, nodeSize)
                        y: PositionCalculator.calculateNodeYOffset(index, 100, graphYOffset)
                        color: nodeKey.focus ? Colors.getSelectedNodeColor() : Colors.getElementColor(index)
                        border.color: Colors.getBorderColor()
                        border.width: 1

                        TextInput {
                            id: nodeKey
                            anchors.centerIn: parent
                            padding: 15
                            focus: editorModel.currentlySelectedNodeIndex === index
                            color: Colors.getNodeKeyColor()

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

                            onFocusChanged: {
                                if (focus) {
                                    for (let i = 0; i < maxSize; i++)
                                        array.itemAt(i).color = Colors.getElementColor(i)

                                    array.itemAt(index).color = Colors.getSelectedNodeColor()

                                }
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
        }

        Section {
            id: controlPanel
            height: visualizeButton.height + 20

            RowLayout {
                width: parent.width

                RowLayout {
                    Layout.alignment: Qt.AlignLeft
                    spacing: 5

                    StyledButton {
                        enabled: editorModel.tree.length < maxSize
                        text: globals.language === "hu" ? "Csúcs hozzáadása" : "Add node"
                        Layout.alignment: Qt.AlignLeft

                        onClicked: {
                            syncTree()
                            editorModel.addNode()
                        }
                    }

                    StyledButton {
                        enabled: editorModel.tree.length > 0
                        text: globals.language === "hu" ? "Csúcs eltávolítása" : "Remove node"
                        Layout.alignment: Qt.AlignLeft

                        onClicked: {
                            syncTree()
                            editorModel.removeNode()

                            for (let i = 0; i < maxSize; i++) {
                                array.itemAt(i).elementKey.text = editorModel.tree[i] ?? ""
                            }
                        }
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignRight
                    spacing: 5

                    StyledButton {
                        enabled: editorModel.tree.length > 0
                        text: globals.language === "hu" ? "Mentés" : "Save"

                        onClicked: {
                            syncTree()
                            saveVisualizationPopup.open()
                        }
                    }

                    StyledButton {
                        id: visualizeButton
                        enabled: editorModel.tree.length > 0
                        text: globals.language === "hu" ? "Szemléltetés" : "Visualize"
                        color: Colors.getMainButtonColor()
                        hoverColor: Colors.getHoveredMainButtonColor()

                        onClicked: {
                            syncTree()
                            algorithmSelector.open()
                        }
                    }
                }
            }
        }
    }

    Modal {
        id: algorithmSelector
        width: 400
        title: globals.language === "hu" ? "Algoritmus kiválasztása" : "Choose algorithm"

        body: Column {
            spacing: 10

            StyledRadioButton {
                id: heapSortRadioButton
                x: 2
                text: globals.language === "hu" ? "Kupacrendezés" : "Heap sort"
                checked: true
            }

            StyledRadioButton {
                id: removeMaxRadioButton
                text: globals.language === "hu" ? "Maximum kiválasztás" : "Remove max"
            }

            StyledRadioButton {
                id: insertNodeRadioButton
                text: globals.language === "hu" ? "Csúcs beszúrása" : "Add node"
                enabled: editorModel.tree.length < 15
            }

            Row {
                x: 20
                spacing: 10

                Text {
                    text: globals.language === "hu" ? "Kulcs" : "Key"
                    color: Colors.getTextColor()
                    opacity: insertNodeRadioButton.checked ? 1 : 0.5
                }

                Rectangle {
                    anchors.leftMargin: 10
                    width: 50
                    height: newNodeKey.implicitHeight
                    border.color: Colors.getBorderColor()
                    opacity: insertNodeRadioButton.checked ? 1 : 0.5
                    color: Colors.getTextInputColor()
                    radius: 3

                    TextInput {
                        id: newNodeKey
                        width: parent.width
                        padding: 2
                        clip: true
                        enabled: insertNodeRadioButton.checked
                        color: Colors.getTextColor()
                        opacity: enabled ? 1 : 0.5

                        validator: IntValidator {
                            bottom: -999
                            top: 999
                        }
                    }
                }
            }
        }

        footer: RowLayout {
            Layout.alignment: Qt.AlignRight

            CheckBox {
                id: skipHeapificationCheckbox
                text: globals.language === "hu" ? "Kupaccá alakítás átugrása" : "Skip heapification"
                enabled: heapSortRadioButton.checked
                scale: 0.8

                onCheckedChanged: {
                    globals.documentHeapification = !skipHeapificationCheckbox.checked
                }
            }

            StyledButton {
                id: startButton
                text: globals.language === "hu" ? "Start" : "Start"

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
        }
    }

    Modal {
        id: saveVisualizationPopup
        title: globals.language === "hu" ? "Fa mentése" : "Save tree"

        body: Column {
            spacing: 5

            Text {
                text: globals.language === "hu" ? "Fájlnév" : "Save as"
                color: Colors.getTextColor()
            }

            Rectangle {
                anchors.leftMargin: 10
                width: 200
                height: fileName.implicitHeight
                border.color: Colors.getBorderColor()
                color: Colors.getTextInputColor()
                radius: 3

                TextInput {
                    id: fileName
                    width: parent.width
                    padding: 2
                    clip: true
                    color: Colors.getTextColor()
                    text: globals.currentFileName
                    focus: true
                    maximumLength: 32

                    Component.onCompleted: {
                        fileName.selectAll()
                    }

                    validator: RegularExpressionValidator {
                        regularExpression: /^[^<>:"/\\|?*\n\r\t]+$/
                    }
                }
            }
        }

        footer: RowLayout {
            StyledButton {
                text: globals.language === "hu" ? "Mentés" : "Save"

                onClicked: {
                    editorModel.saveVisualization(fileName.text, globals.currentlyEditedTree)

                    saveVisualizationPopup.close()
                }
            }
        }
    }

    Modal {
        id: heapifyPopup
        title: globals.language === "hu" ? "Figyelmeztetés" : "Alert"

        body: Column {
            Text {
                width: 400
                wrapMode: Text.WordWrap
                color: Colors.getTextColor()
                text: globals.language === "hu" ? "A megadott fa nem teljesíti a kupac tulajdonságot. Szeretnéd a fa kupaccá alakított verziójával lejátszani az algoritmust?" : "The provided tree does not satisfy the heap property. Would you like to run the algorithm on a heapified version of the tree?"
            }
        }

        footer: RowLayout {
            spacing: 5

            StyledButton {
                id: yesButton
                text: globals.language === "hu" ? "Igen" : "Yes"

                onClicked: {
                    nodes.model = null
                    Utils.heapify(globals.currentlyEditedTree)
                    switchPage("Visualizer")
                }
            }

            StyledButton {
                id: noButton
                text: globals.language === "hu" ? "Nem" : "No"
                color: Colors.getRedButtonColor()
                hoverColor: Colors.getHoveredRedButtonColor()
                activeColor: Colors.getActiveButtonColor()

                onClicked: {
                    heapifyPopup.close()
                }
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

        for (let k = 0; k < maxSize; k++) {
            if (nodes.itemAt(k))
                nodes.itemAt(k).nodeKey.focus = false

            array.itemAt(k).color = Colors.getElementColor(k)
        }
    }
}
