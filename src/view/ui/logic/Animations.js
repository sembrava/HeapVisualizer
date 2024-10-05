function swapNodes(nodes, greaterNodeIndex, smallerNodeIndex) {
    // smaller x
    nodes.itemAt(smallerNodeIndex)
        .swapAnimation
            .animations[0] // sequential
            .animations[0] // parallel
            .animations[0] // number
            .to = (nodes.itemAt(greaterNodeIndex).x + nodes.itemAt(smallerNodeIndex).x) / 2

    // smaller y
    nodes.itemAt(smallerNodeIndex)
        .swapAnimation
            .animations[0] // sequential
            .animations[0] // parallel
            .animations[1] // number
            .to = (nodes.itemAt(greaterNodeIndex).y + nodes.itemAt(smallerNodeIndex).y) / 2

    // greater x
    nodes.itemAt(greaterNodeIndex)
        .swapAnimation
            .animations[0] // sequential
            .animations[0] // parallel
            .animations[0] // number
            .to = (nodes.itemAt(greaterNodeIndex).x + nodes.itemAt(smallerNodeIndex).x) / 2

    // greater y
    nodes.itemAt(greaterNodeIndex)
        .swapAnimation
            .animations[0] // sequential
            .animations[0] // parallel
            .animations[1] // number
            .to = (nodes.itemAt(greaterNodeIndex).y + nodes.itemAt(smallerNodeIndex).y) / 2

    nodes.itemAt(smallerNodeIndex).swapAnimation.start()
    nodes.itemAt(greaterNodeIndex).swapAnimation.start()
}
