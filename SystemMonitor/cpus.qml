import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.2

Item {
    id: cpuItem

    property var key;
    property var val;

    function castStringToFloat(stringValue) {
        var floatValue = parseFloat(stringValue);
        return floatValue;
    }

    // TODO: GRID LAYOUT ALIGN
    GridLayout {
        id: rowLayout
        width: parent.width
        columns: 2

        Text {
            font.pixelSize: 16
            text: "<b>" + key + "</b>" + " : " + " " + val + "%"
        }

        ProgressBar {
            from: 0
            to: 100
            value: castStringToFloat(val)

//            background: Rectangle {
//                color: "lightgreen"
//                radius: 4
//                border.width: 1
//                border.color: Style.appBackgroundColor
//            }
        }
    }
}
