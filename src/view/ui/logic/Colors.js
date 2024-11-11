Qt.include("PositionCalculator.js")

function getElementColor(theme, index) {
    const level = getLevel(index);

    switch (level) {
        case 0:
            return "#8899A6"; // Medium Slate Gray
        case 1:
            return "#A2B1BA"; // Soft Steel Gray
        case 2:
            return "#BCC5CC"; // Light Smoky Gray
        case 3:
            return "#D1D8DD"; // Light Cool Gray
        default:
            return "#E3E7EA"; // Soft Light Gray
    }
}
