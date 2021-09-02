import QtQuick 2.12

Item {
    id: otherItem

    property var key;
    property var value;

    Text {
        font.pixelSize: 16
        text: "<b>" + key + "</b>" + " : " + " " + value + "%"
    }
}
