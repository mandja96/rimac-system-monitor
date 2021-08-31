import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Window {

    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("System Monitor: by Anđa")

    function testFunction(cpuInfo) {
        console.log("AAAA")

        for (var prop in cpuInfo) {
            console.log("Object item:", prop, "=", cpuInfo[prop])
        }
    }

    Button {
        id: myButton
        anchors.centerIn: parent
        text: "Click me!"
        onClicked: testFunction(cpuInfo.getCpuLoad());
    }

    ColumnLayout {
        Text {
            id: numberOfThreads
            font.pixelSize: 18
            text: "# threads: " + threadsInfo.numberOfThreads
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: "black"
        }

        Text {
            id: numberOfProcesses
            font.pixelSize: 18
            text: "# processes: " + processesInfo.numberOfProcesses
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            color: "black"
        }

        Text {
            id: availableMemory
            font.pixelSize: 18
            text: "Available Memory: " + memoryInfo.availableMemory
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: "black"
        }

        Text {
            id: usedMemory
            font.pixelSize: 18
            text: "Used Memory: " + memoryInfo.usedMemory
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: "black"
        }

        Text {
            id: cacheMemmory
            font.pixelSize: 18
            text: "Cache Memory: " + memoryInfo.cacheMemory
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: "black"
        }

        Text {
            id: totalMemory
            font.pixelSize: 18
            text: "Total Memory: " + memoryInfo.totalMemory
        }
    }

    Frame {
        ListView {
        }
    }
}
