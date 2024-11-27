pragma Singleton
import QtQuick

QtObject {
    property real screenWidth: 1920
    property real screenHeight: 1080
    property real spacing: 25
    property int fontSize: 24
    property int borderWidth: 3
    property int radius: 50
    property real disabledOpacity: 0.5

    property bool darkMode: true
    property Theme currentTheme: darkMode ? darkTheme : lightTheme

    property Theme darkTheme: Theme {
        foreground: "#ffffff"
        primary: "#142e7c"
        accent: "#f97924"

        success: "#0db002"
        warning: "#f97924"
        error: "#ff0000"

        background: "#5d768a"
        darkBackground: "#465968"

        cut: "#e6c602"
        coagulate: "#0795cd"
    }

    property Theme lightTheme: Theme {
        foreground: "#142e7c"
        primary: "#ffffff"
        accent: "#f97924"

        success: "#0db002"
        warning: "#f97924"
        error: "#ff0000"

        background: "#b6b6b6"
        darkBackground: "#5d768a"

        cut: "#e6c602"
        coagulate: "#0795cd"
    }

}
