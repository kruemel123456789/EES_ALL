import QtQuick 2.2

BasePage {
    height: parent.height; width: parent.width

    titel: "Personal"

    menuButtonsText: [ "back", "next" ]

    Rectangle {
        anchors.fill: parent
        color: "lightsteelblue"

        Text{
            id: textId
            anchors.centerIn: parent
            text:"person Page"
            font.pixelSize: 24
        }
    }

    onMenuButtonClicked: {
        switch ( buttonIndex ) {
        case 0: mainStackView.pop(); break;
        case 1: mainStackView.push( dailyRoutinePage ); break;
        default: console.log("error")
        }
    }
}

