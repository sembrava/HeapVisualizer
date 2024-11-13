Qt.include("PositionCalculator.js")

function getElementColor(theme, index) {
    const level = getLevel(index);

    switch (level) {
        case 0:
            return "#8899A6";
        case 1:
            return "#A2B1BA";
        case 2:
            return "#BCC5CC";
        case 3:
            return "#D1D8DD";
        default:
            return "#E3E7EA";
    }
}

function getButtonColor() {
    return "#0949b0";
}

function getHoveredButtonColor () {
    return "#05327a";
}
