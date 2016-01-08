import QtQuick 2.3
import QtQuick.Window 2.2

import com.biotron.boardcontroller 1.0

Window {
    visible: true
    width: 640
    height: 480

    Rectangle {
        color: "gray"
        anchors.fill: parent

//        Row {
//            id: insertionUIthings
//            width: parent.width * 2 / 3
//            x: parent.width / 6
//            y: 20
//            height: 50

//            Repeater {
//                model: 7
//                Rectangle {
//                    color: "#555555"
//                    width: parent.width / 7
//                    height: 50
//                    radius: 10

//                    Text {
//                       text: "Insert Column: " + index
//                       anchors.centerIn: parent
//                       width: parent.width
//                       wrapMode: Text.WordWrap
//                    }
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
//                            BoardController.insertAtColumn(index);
//                        }
//                    }
//                }
//            }
//        }

        Text {
            text: "Connect 4"
            x: parent.width / 2 - width / 2
            y: 10
            font.pointSize: 20
            color: "#333333"
        }

        Column {
            id: boardColumn
            width: parent.width * 2 / 3
            x: parent.width / 6
            y: parent.height / 8 + 50

            spacing: 6
            Repeater {
                model: 6
                Connect4Row {
                    sspacing: 6
                    rowDataArray: BoardController.gameBoard
                    offset: index*7
                    width: parent.width

                }
            }
        }

//        Rectangle {
//            color: "#0000D0"
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//            width: 100
//            height: 50
//            radius: 7

//            Text {
//                anchors.centerIn: parent
//                text: "Reset board"
//            }

//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    BoardController.reset();
//                }
//            }
//        }
    }
}

