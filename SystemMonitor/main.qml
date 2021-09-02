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
    color: "#d3d3d3"

    function testFunction(diskInfo) {
        console.log("AAAA")

        for (var prop in diskInfo.solidDisksVariantMap) {
            //console.log("prop = ", prop)
            console.log("Object item:", prop, "=", diskInfo.solidDisksVariantMap[prop])
        }
    }

    property var recentCPUTextLabels: [];
    property var recentDiskTextLabels: [];

    function createDiskObjects() {
        var i = 0
        var info = diskInfo.solidDisksVariantMap

        if (recentDiskTextLabels.length != 0) {
            for (var p = recentDiskTextLabels.length; p > 0; p--) {
                recentDiskTextLabels[p-1].destroy(0);
                recentDiskTextLabels.pop();
            }
         }

        var component = Qt.createComponent("disks.qml");
        if (component.status === Component.Ready) {
            for (var disk in info) {
                //console.log("Object item:", cpu, "=", info[cpu])
                var disks = component.createObject(diskLabel,
                                                {y: i*50, key: disk, values: info[disk]});
                if (disks === null) {
                    // Error Handling
                    console.log("Error creating object DISKS");
                }

                recentDiskTextLabels.push(disks);
                i = i+1
            }
        }
        else {
            console.log("disks.qml not created")
        }

        // because text is expecting QString
        return ""
    }

    function createCPUsObjects() {
        var i = 0
        var info = cpuInfo.cpuMap;

        if (recentCPUTextLabels.length != 0) {
            for (var p = recentCPUTextLabels.length; p > 0; p--) {
                recentCPUTextLabels[p-1].destroy();
                recentCPUTextLabels.pop();
            }
        }

        var component = Qt.createComponent("cpus.qml");
        if (component.status === Component.Ready) {
            for (var cpu in info) {
                //console.log("Object item:", cpu, "=", info[cpu])
                var cpus = component.createObject(cpuLabel,
                                                {y: i*30, key: cpu, val: info[cpu]});

                if (cpus === null) {
                    // Error Handling
                    console.log("Error creating object CPUs");
                }

                recentCPUTextLabels.push(cpus);
                i = i+1
            }
        } else {
            console.log("cpus.qml not created")
        }

        return ""
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
                    color: "green"
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
                    color: "red"
                    text: "Used Memory: " + memoryInfo.usedMemory + " [MiB]"
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: "#d3d3d3"
                }

                Text {
                    id: totalMemory
                    font.pixelSize: 18
                    color: "blue"
                    text: "Total Memory: " + memoryInfo.totalMemory + " [MiB]"

                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 5
                    color: "black"
                }

                Text {
                    id: cacheMemory
                    font.pixelSize: 18
                    text: "Cache Memory: " + memoryInfo.cacheMemory + " [MiB]"
                }
            }
        }
        Item {
            id: diskTab

            ColumnLayout {
                id: diskLayout

                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 100
                    leftMargin: 100
                }

                Text {
                    id: diskLabel
                    text: {
                        createDiskObjects()
                    }
                }

                //Component.onCompleted: createDiskObjects()
            }
        }
    }
}
