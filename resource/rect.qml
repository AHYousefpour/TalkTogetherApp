import QtQuick 2.15

Rectangle {
    width: 800;
    height: 600;
    gradient: Gradient {
        orientation: Gradient.Vertical
        GradientStop {
            position: 0
            color: "#243949"
        }

        GradientStop {
            position: 1
            color: "#517fa4"
        }
    }
}
