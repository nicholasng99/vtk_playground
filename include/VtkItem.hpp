#pragma once
#include <QQuickVTKItem.h>

class VtkItem : public QQuickVTKItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override;
};