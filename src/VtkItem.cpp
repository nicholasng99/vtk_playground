#include "VtkItem.hpp"

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QtGui/QGuiApplication>
#include <QtGui/QSurfaceFormat>

#include <QVTKRenderWindowAdapter.h>

#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

QQuickVTKItem::vtkUserData VtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    // Create a cone pipeline and add it to the view
    vtkNew<vtkConeSource> cone;

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cone->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->SetBackground(0.0, 1.0, 1.0);
    renderer->SetBackground2(1.0, 0.0, 0.0);
    renderer->SetGradientBackground(true);

    renderWindow->AddRenderer(renderer);
    renderWindow->SetMultiSamples(16);

    return nullptr;
}