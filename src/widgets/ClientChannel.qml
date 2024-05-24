import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import model.channel as Model
import model.myFile as Model
import model.file as Model
import network.client as Network

Rectangle {
    id: root
    color: "#3F4246"

    required property Model.Channel channel
    property int currentIndex: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            Layout.fillWidth: false
            Layout.preferredWidth: parent.width - 20
            Layout.margins: 10
            spacing: 10

            ColumnLayout {
                Label {
                    text: root.channel.address + ":" + root.channel.port
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                id: startButton
                text: qsTr("Start")
                enabled: network.status === Network.Client.Unconnected

                onClicked: network.start(root.channel.address, root.channel.port)
            }

            Button {
                id: stopButton
                text: qsTr("Stop")
                enabled: network.status === Network.Client.Connected

                onClicked: network.stop()
            }
        }

        Row {
            id: flowView
            width: parent.width
            Layout.fillWidth: true
            Layout.preferredWidth: parent.width - 20
            Layout.margins: {
                top: 0
                right: 10
                bottom: 0
                left: 10
            }
            spacing: 10

            Tag {
                text: qsTr("My Files")
                active: stackView.currentIndex == 0

                onClicked: {
                    stackView.currentIndex = 0;
                }
            }

            Repeater {
                model: network.connections

                Tag {
                    text: modelData.address
                    active: stackView.currentIndex == index + 1

                    onClicked: {
                        stackView.currentIndex = index + 1;
                    }
                }
            }
        }

        Rectangle {
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: "#1E1E1E"

            StackLayout {
                id: stackView
                anchors.fill: parent
                currentIndex: 0

                Flickable {
                    id: flickable
                    flickableDirection: Flickable.VerticalFlick
                    contentHeight: content.height
                    topMargin: 0
                    clip: true


                    ColumnLayout {
                        id: content
                        width: parent.width
                        spacing: 10

                        Item { }

                        Repeater {
                            model: network.myFiles
                            delegate: MyFile {
                                required property Model.MyFile modelData

                                Layout.preferredWidth: parent.width - 16
                                Layout.alignment: Qt.AlignHCenter
                                file: modelData

                                onRemove: network.removeMyFile(modelData)
                            }
                        }
                    }
                }

                Repeater {
                    model: network.connections
                    delegate: Flickable {
                        flickableDirection: Flickable.VerticalFlick
                        contentHeight: content.height
                        topMargin: 0
                        clip: true

                        ColumnLayout {
                            id: content
                            width: parent.width
                            spacing: 10

                            Item { }

                            Repeater {
                                model: modelData.files
                                delegate: File {
                                    required property Model.File modelData

                                    Layout.preferredWidth: parent.width - 16
                                    Layout.alignment: Qt.AlignHCenter
                                    file: modelData

                                    onDownload: network.requestDownloadFile(modelData)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        property bool dragging: false

        onEntered: (drag) => {
            if (drag.hasUrls) {
                drag.accepted = true;
            } else {
                drag.accepted = false;
            }
            dropArea.dragging = true;
        }
        onDropped: (drop) => {
            dropArea.dragging = false;
            network.addMyFiles(drop.urls);
        }

        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.2
            visible: dropArea.dragging
        }
    }

    Network.Client {
        id: network

        onConnectionsChanged: {
            console.log("Client Channel Connections Changed");
            if (stackView.currentIndex !== 0) {
                if (network.connections.length === 0) {
                    stackView.currentIndex = 0;
                } else if (stackView.currentIndex < network.connections.length) {
                    stackView.currentIndex = network.connections.length;
                }
            }
        }

        onDisconnected: {
            console.log("Client Channel Disconnected");
        }

        onConnectError: {
            messageDialog.open();
        }
    }

    MessageDialog {
        id: messageDialog
        text: qsTr("Failed to connect to server!")
        buttons: MessageDialog.Ok
    }

    Component.onDestruction: console.log("Client Channel Destruction Beginning!")
}
