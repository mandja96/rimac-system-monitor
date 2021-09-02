import QtQuick 2.0

Item {
    id: diskOtherItem

    property var key;
    property var values;

    Text {
        font.pixelSize: 16
        text: "DEVICE -- " + "<b>" + key + "</b> || " + " total: " + values[0] + " || available: " + values[1] + " || used: " + values[2];
    }
}

