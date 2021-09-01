import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Rectangle {
    width: 80;
    height: 50;
    color: "red"

    property var cpusInfo: "A";

    Text {
        text: cpusInfo
    }
}
