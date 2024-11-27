import QtQuick
import QtQuick.Controls

import Style
import Utility

ApplicationWindow {
    visible: true
    title: qsTr("Project Name")
    width: Style.screenWidth
    height: Style.screenHeight

    Component.onCompleted: {
        console.log(Settings.getValue("Language"));
    }
}
