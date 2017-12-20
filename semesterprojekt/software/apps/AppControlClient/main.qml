import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: applicationWindow
    width: 1024
    height: 580
    
    
    
    signal doPlatformConnect()
    signal doPlatformFeedbackMove(int workstate)
    signal doPlatformServerToggle()
    
    signal doRobotConnect()
    signal doRobotFeedbackMove(int workstate)
    signal doRobotServerToggle()
    
    signal doAppControlServerToggle()
    signal doAppControlGetMethods()
    signal doPlatformAppControlTestConnect(string address);
    signal doRobotAppControlTestConnect(string address);
    signal doPlatformAppControlMoveRequest(int userid)
    signal doRobotAppControlMoveRequest(int movementid, int glassid)
    
    
    GroupBox {
        id: groupPlatform
        y: 0
        width: parent.width * 0.3
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        title: qsTr("")
        
        Button {
            id: btnPlatformFeedbackMove
            x: 0
            y: 168
            text: qsTr("platform_appcontrol_feedback_move")
            onClicked: doPlatformFeedbackMove(parseInt(txtPlatformFeedbackMove.text));
        }
        
        TextField {
            id: txtPlatformFeedbackMove
            x: 193
            y: 170
            width: 62
            height: 20
            inputMethodHints: Qt.ImhDigitsOnly
            placeholderText: qsTr("workState")
        }
        
        Button {
            id: btnPlatformToggleServer
            y: 9
            height: 23
            text: qsTr("Start Platform Test-Server")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: doPlatformServerToggle()
            Connections {
                target: server_platform
                onStatusChanged:
                {
                    btnPlatformToggleServer.text = (!serverRunning ? "Start" : "Stop") + " Platform Test-Server"
                }
            }
        }
        
        Label {
            id: label6
            x: 0
            y: 149
            text: qsTr("Send to AppControl:")
        }

        TextArea {
            id: textLogPlatform
            y: 400
            height: 115
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Label {
            id: label2
            x: 137
            y: 381
            text: qsTr("Log")
        }
    }
    
    GroupBox {
        id: groupRobot
        x: parent.width * 0.70
        width: parent.width * 0.30
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        title: qsTr("")
        
        Button {
            id: btnRobotFeedbackMove
            x: 2
            y: 168
            text: qsTr("robot_appcontrol_feedback_move")
            onClicked: doRobotFeedbackMove(parseInt(txtRobotFeedbackMove.text));
        }
        
        TextField {
            id: txtRobotFeedbackMove
            x: 181
            y: 170
            width: 62
            height: 20
            inputMethodHints: Qt.ImhDigitsOnly
            placeholderText: qsTr("workState")
        }
        
        Button {
            id: btnRobotToggleServer
            y: 9
            height: 23
            text: qsTr("Start Robot Test-Server")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            onClicked: doRobotServerToggle()
            Connections {
                target: server_robot
                onStatusChanged:
                {
                    btnRobotToggleServer.text = (!serverRunning ? "Start" : "Stop") + " Robot Test-Server"
                }
            }
        }
        
        Label {
            id: label7
            x: 0
            y: 149
            text: qsTr("Send to AppControl:")
        }

        TextArea {
            id: textLogRobot
            y: 400
            height: 115
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Label {
            id: label4
            x: 137
            y: 381
            text: qsTr("Log")
        }
    }
    

    
    Connections
    {
        target: server_platform
        onNewMessage:
        {
            textLogPlatform.append("[" + servername + "] " + message)
        }
        
    }
    
    Connections
    {
        target: server_robot
        onNewMessage:
        {
            textLogRobot.append("[" + servername + "] " + message)
        }
        
    }
    
    


    Connections
    {
        target: client_appcontrol_platform
        onNewMessage:
        {
            textLogAppControl.append("[" + clientname + "] " + message)
        }
        onConnectedChanged:
        {
            btnPlatformAppControlConnect.enabled = !connectionState
            btnPlatformAppControlConnect.text = (!connectionState ? "Connect to Platform Server" : "Connected to Platform Server")
        }

    }

    Connections
    {
        target: client_appcontrol_robot
        onNewMessage:
        {
            textLogAppControl.append("[" + clientname + "] " + message)
        }
        onConnectedChanged:
        {
            btnRobotAppControlConnect.enabled = !connectionState
            btnRobotAppControlConnect.text = (!connectionState ? "Connect to Robot Server" : "Connected to Robot Server")
        }

    }


    GroupBox {
        id: groupBoxAppControl
        x: parent.width * 0.30
        width: parent.width * 0.4
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        title: qsTr("")


        Button {
            id: btnPlatformAppControlConnect
            x: 0
            y: 70
            width: 195
            height: 23
            text: qsTr("Connect to Platform Server")
            onClicked: doPlatformAppControlTestConnect(txtAppControlPlatformServerAddress.text)
        }

        Button {
            id: btnRobotAppControlConnect
            x: 201
            y: 70
            width: 193
            height: 23
            text: qsTr("Connect to Robot Server")
            onClicked: doRobotAppControlTestConnect(txtAppControlRobotServerAddress.text)
        }

        TextArea {
            id: textLogAppControl
            y: 400
            height: 115
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.rightMargin: 0
        }

        Label {
            id: label3
            x: 188
            y: 381
            text: qsTr("Log")
        }

        GroupBox {
            id: groupBoxAppControlPlatformMove
            x: 0
            y: 150
            width: 195
            height: 132
            title: qsTr("appcontrol_platform_move")

            Button {
                id: btnPlatformAppControlMoveRequest
                x: 0
                y: 86
                width: 179
                height: 23
                text: qsTr("Send")
                enabled: false
                onClicked: doPlatformAppControlMoveRequest(txtAppControlPlatformMoveUserId.text);
                Connections
                {
                    target: client_appcontrol_platform
                    onConnectedChanged:
                    {
                        btnPlatformAppControlMoveRequest.enabled = connectionState
                    }
                }
            }

            TextField {
                id: txtAppControlPlatformMoveUserId
                x: 0
                y: 36
                width: 179
                height: 20
                placeholderText: qsTr("userId")
            }
        }

        GroupBox {
            id: groupBoxAppControlRobotMove
            x: 201
            y: 150
            width: 193
            height: 132
            title: qsTr("appcontrol_robot_move")

            Button {
                id: btnRobotAppControlMoveRequest
                x: 0
                y: 86
                width: 177
                height: 23
                text: qsTr("Send")
                onClicked: doRobotAppControlMoveRequest(parseInt(txtAppControlRobotMoveMovementId.text), parseInt(txtAppControlRobotMoveGlassId.text));
                enabled: false
                Connections
                {
                    target: client_appcontrol_robot
                    onConnectedChanged:
                    {
                        btnRobotAppControlMoveRequest.enabled = connectionState
                    }
                }
            }

            TextField {
                id: txtAppControlRobotMoveMovementId
                x: 0
                y: 24
                width: 179
                height: 20
                placeholderText: qsTr("movementId")
            }

            TextField {
                id: txtAppControlRobotMoveGlassId
                x: 0
                y: 50
                width: 179
                height: 20
                placeholderText: qsTr("glassId")
            }
        }

        TextField {
            id: txtAppControlPlatformServerAddress
            x: 0
            y: 44
            width: 195
            height: 20
            text: qsTr("localhost")
            placeholderText: qsTr("Platform Server IP")
        }

        TextField {
            id: txtAppControlRobotServerAddress
            x: 201
            y: 44
            width: 195
            height: 20
            text: qsTr("localhost")
            placeholderText: qsTr("Robot Server IP")
        }


    }

    Label {
        id: label
        x: 114
        y: 9
        text: qsTr("Platform")
        font.pointSize: 16
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label1
        x: 460
        y: 9
        text: qsTr("AppControl")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 16
    }

    Label {
        id: label5
        x: 844
        y: 9
        text: qsTr("Robot")
        font.pointSize: 16
        horizontalAlignment: Text.AlignHCenter
    }


    
    
    Component.onCompleted: show()
}
