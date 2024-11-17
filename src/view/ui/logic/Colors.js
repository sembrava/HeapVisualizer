Qt.include("PositionCalculator.js")

function getBackgroundColor() {
    return globals.isLightTheme ? "#DDD" : "#101317"
}

function getSectionColor() {
    return globals.isLightTheme ? "#EFEFEF" : "#171D22"
}

function getPrimaryDetailColor() {
    return globals.isLightTheme ? "#DADADA" : "#20262C"
}

function getSecondaryDetailColor() {
    return globals.isLightTheme ? "#E4E4E4" : "#2C333A"
}

function getTextColor() {
    return globals.isLightTheme ? "#000" : "#FFF"
}

function getLighterTextColor() {
    return globals.isLightTheme ? "#222" : "#DDD"
}

function getButtonTextColor() {
    return "#FFF"
}

function getButtonColor() {
    return "#5C9FD6";
}

function getHoveredButtonColor() {
    return "#4A8BD4";
}

function getActiveButtonColor() {
    return "#2A6A91";
}

function getMainButtonColor() {
    return "#3C7EB8";
}

function getHoveredMainButtonColor() {
    return "#2D5E8C";
}

function getRedButtonColor() {
    return "#F15B5B";
}

function getHoveredRedButtonColor() {
    return "#EC3D3D";
}

function getActiveRedButtonColor() {
    return "#D91F1F";
}

function getSidebarButtonColor() {
    return "#BBB";
}

function getHoveredSidebarButtonColor() {
    return "#AAA"
}

function getTextInputColor() {
    return globals.isLightTheme ? "#FFF" : "#000"
}

function getBorderColor() {
    return globals.isLightTheme ? "#CCC" : "#999"
}

function getElementColor(index) {
    const level = getLevel(index);

    if (globals.isLightTheme) {
        switch (level) {
            case 0:
                return "#7D6B72";
            case 1:
                return "#8D7B5E";
            case 2:
                return "#6A7885";
            default:
                return "#6A7F72";
        }
    }

    else {
        switch (level) {
            case 0:
                return "#7D6B72";
            case 1:
                return "#8D7B5E";
            case 2:
                return "#6A7885";
            default:
                return "#6A7F72";
        }
    }
}

function getIndexColor() {
    return "#000";
}

function getNodeKeyColor() {
    return "#222"
}

function getSelectedNodeColor() {
    return "#FF6F00";
}

function getSecondarySelectedNodeColor() {
    return "#FF0000";
}

function getSortedNodeColor() {
    return "#00FF00";
}

function getNodeBackgroundColor() {
    return globals.isLightTheme ? "#DDD" : "#444";
}

function getExtractedNodeColor() {
    return "#007BFF"
}
