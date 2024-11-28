#pragma once
#include <QQuickVTKItem.h>

#include <vtkSmartPointer.h>
#include <vtkObject.h>

class vtkActor;
class vtkRenderer;

class ModelViewer : public QQuickVTKItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

public:
    struct Data : vtkObject
    {
        static Data *New();
        vtkTypeMacro(Data, vtkObject);

        vtkNew<vtkActor> actor;
        vtkNew<vtkRenderer> renderer;
    };

    ModelViewer();
    vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override;
    void destroyingVTK(vtkRenderWindow *renderWindow, vtkUserData userData) override;
    double value() const;

signals:
    void valueChanged();

public slots:
    void setValue(double value);

private:
};