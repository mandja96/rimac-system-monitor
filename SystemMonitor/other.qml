import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

Item {
    property var key;
    property var value;

    Text {
        font.pixelSize: 16
        text: "<b>" + key + "</b>" + " : " + " " + value + "%"
    }
}
