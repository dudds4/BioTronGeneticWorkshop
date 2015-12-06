import QtQuick 2.0

Row {
    /* Set this array to hold data for each cell state :D */
    property var rowDataArray;
    property int offset: 0;

    /* Some sweet spacing/positioning math */
    width: parent.width
    property int itemsPerRow: 7
    property int sspacing: 4
    spacing: sspacing

    function colourFromPlayerNum(playerNum) {
        if(playerNum === 1) {
            return "red";
        } else if(playerNum === 2) {
            return "blue";
        }
        return "white";
    }

    Repeater {
        model: itemsPerRow
        Rectangle {
            color: (rowDataArray.length && rowDataArray.length >= offset + 7) ?
                colourFromPlayerNum(rowDataArray[index + offset]) :
                "white"
            property int r: (parent.width - sspacing * (itemsPerRow - 1)) / (itemsPerRow * 2)
            height: r * 2
            width: r * 2
            radius: r
        }
    }
}

