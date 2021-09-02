import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3

Window {

    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("System Monitor: by Anđa")
    Material.accent: Material.DeepOrange
    color: "#ffffff"

    function testFunction(cpuInfo) {
        console.log("AAAA")

        for (var prop in cpuInfo) {
            console.log("Object item:", prop, "=", cpuInfo[prop])
        }
    }

    property var recentCPUTextLabels: [];

    function createCPUsObjects() {
        var i = 0
        var info = cpuInfo.cpuMap;

        if (recentCPUTextLabels.length != 0) {
            for (var p = recentCPUTextLabels.length; p > 0; p--) {
                console.log("Broj dece: ", recentCPUTextLabels[p-1].children.length)
                recentCPUTextLabels[p-1].destroy();
            }
        }
        recentCPUTextLabels.length = 0;
        recentCPUTextLabels = [];

        var component = Qt.createComponent("other.qml");
        if (component.status === Component.Ready) {
            for (var cpu in info) {
                //console.log("Object item:", cpu, "=", info[cpu])
                var cpus = component.createObject(cpuLabel,
                                                {y: i*20, key: cpu, value: info[cpu]});

                if (cpus === null) {
                    // Error Handling
                    console.log("Error creating object CPUs");
                }

                recentCPUTextLabels.push(cpus);
                i = i+1
            }
        } else {
            console.log("other.qml not created")
        }

    }

    TabBar {
        id: bar
        width: parent.width

        TabButton {
            text: qsTr("CPUs")
        }
        TabButton {
            text: qsTr("Threads/Processes")
        }
        TabButton {
            text: qsTr("Memory")
        }
        TabButton {
            text: qsTr("Disk")
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex

        Item {
            id: cpuTab

            ColumnLayout {
                id: cpuLayout
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 100
                    leftMargin: 100
                    //horizontalCenter: parent.horizontalCenter
                }
//                Button {
//                    id: myButton2
//                    text: "Click me!"
//                    onClicked: testFunction(cpuInfo.cpuMap)
//                }

                Text {
                    id: cpuLabel
                    text: {
                        createCPUsObjects()
                    }
                }

//                Button {
//                    id: cpuLabel
//                    onClicked: {
//                        createCPUsObjects()
//                    }
//                }

            }
        }
        Item {
            id: tpTab

            ColumnLayout {
                anchors {
                    top: parent.top
                    topMargin: 100
                    horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: numberOfThreads
                    font.pixelSize: 18
                    text: "Number of Threads: " + threadsInfo.numberOfThreads
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 10
                    color: "black"
                }

                Text {
                    id: numberOfProcesses
                    font.pixelSize: 18
                    text: "Number of Processes: " + processesInfo.numberOfProcesses
                }
            }
        }
        Item {
            id: memoryTab

            ColumnLayout {
                anchors {
                    top: parent.top
                    topMargin: 100
                    horizontalCenter: parent.horizontalCenter
                }
                Text {
                    id: availableMemory
                    font.pixelSize: 18
                    text: "Available Memory: " + memoryInfo.availableMemory + " [MiB]"
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 5
                    color: "black"
                }

                Text {
                    id: usedMemory
                    font.pixelSize: 18
                    text: "Used Memory: " + memoryInfo.usedMemory + " [MiB]"
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: "white"
                }

                Text {
                    id: totalMemory
                    font.pixelSize: 18
                    text: "Total Memory: " + memoryInfo.totalMemory + " [MiB]"

                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 5
                    color: "black"
                }

                Text {
                    id: cacheMemmory
                    font.pixelSize: 18
                    text: "Cache Memory: " + memoryInfo.cacheMemory + " [MiB]"
                }
            }
        }
        Item {
            id: diskTab
        }
    }

//    ColumnLayout {
//        anchors {
//            top: parent.top
//            topMargin: 100
//        }

//        Text {
//            id: numberOfThreads
//            font.pixelSize: 18
//            text: "# threads: " + threadsInfo.numberOfThreads
//        }

//        Rectangle {
//            Layout.fillWidth: true
//            Layout.preferredHeight: 2
//            color: "black"
//        }

//        Text {
//            id: numberOfProcesses
//            font.pixelSize: 18
//            text: "# processes: " + processesInfo.numberOfProcesses
//        }

//        Rectangle {
//            Layout.fillWidth: true
//            Layout.preferredHeight: 100
//            color: "black"
//        }

//        Text {
//            id: availableMemory
//            font.pixelSize: 18
//            text: "Available Memory: " + memoryInfo.availableMemory
//        }

//        Rectangle {
//            Layout.fillWidth: true
//            Layout.preferredHeight: 2
//            color: "black"
//        }

//        Text {
//            id: usedMemory
//            font.pixelSize: 18
//            text: "Used Memory: " + memoryInfo.usedMemory
//        }

//        Rectangle {
//            Layout.fillWidth: true
//            Layout.preferredHeight: 2
//            color: "black"
//        }

//        Text {
//            id: cacheMemmory
//            font.pixelSize: 18
//            text: "Cache Memory: " + memoryInfo.cacheMemory
//        }

//        Rectangle {
//            Layout.fillWidth: true
//            Layout.preferredHeight: 2
//            color: "black"
//        }

//        Text {
//            id: totalMemory
//            font.pixelSize: 18
//            text: "Total Memory: " + memoryInfo.totalMemory

//        }
//    }
//    ListView {
//        id: cpu
//        anchors {
//            top: parent.top
//            topMargin: 100
//            horizontalCenter: parent.horizontalCenter
//        }
//        property var cpus : cpuInfo.getCpuLoad()

//        Text {
//            text: "Andja :("
//        }
//    }
}
