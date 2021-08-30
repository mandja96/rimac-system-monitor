import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {

    width: 640
    height: 480
    visible: true
    title: qsTr("System Monitor")

//    Button {
//        id: myButton
//        anchors.centerIn: parent
//        text: "Click me!"
//        onClicked: threadsInfo.setNumberOfThreads(10)
//    }

    Text {
        id: numberOfThreads
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 20
        }
        font.pixelSize: 24
        text: threadsInfo.numberOfThreads
    }

    Text {
        id: numberOfProcesses
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: 100
        }
        font.pixelSize: 24
        text: processesInfo.numberOfProcesses
    }

}
