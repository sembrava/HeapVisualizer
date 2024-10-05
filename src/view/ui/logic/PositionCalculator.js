function getLevel(index) {
    return Math.floor(Math.log2(index + 1));
}

function getNodeCountByLevel(level) {
    return Math.pow(2, level)
}

function getNodePositionWithinLevel(index, level) {
    return index - (Math.pow(2, level) - 1) + 1
}

function calculateNodeXOffset(index, totalWidth, nodeSize) {
    const level = getLevel(index)
    const nodeCount = getNodeCountByLevel(level)
    const spaceTakenUpByNodes = nodeCount * nodeSize
    const spaceBetweenNodes = (totalWidth - spaceTakenUpByNodes) / (nodeCount + 1)
    const positionWithinLevel = getNodePositionWithinLevel(index, level)

    return positionWithinLevel * nodeSize + positionWithinLevel * spaceBetweenNodes - nodeSize
}

function calculateNodeYOffset(index, paddingBetweenLevels, topPadding) {
    return getLevel(index) * paddingBetweenLevels + topPadding
}

function calculateEdgeStartXOffset(index, totalWidth, nodeSize) {
    return calculateNodeXOffset(getParent(index), totalWidth, nodeSize) + nodeSize / 2
}

function calculateEdgeStartYOffset(index, paddingBetweenLevels, topPadding, nodeSize) {
    return calculateNodeYOffset(getParent(index), paddingBetweenLevels, topPadding) + nodeSize
}

function calculateEdgeEndXOffset(index, totalWidth, nodeSize) {
    return calculateNodeXOffset(index, totalWidth, nodeSize) + nodeSize / 2
}

function calculateEdgeEndYOffset(index, paddingBetweenLevels, topPadding) {
    return calculateNodeYOffset(index, paddingBetweenLevels, topPadding)
}

function getParent(index) {
    return Math.floor((index - 1) / 2)
}
