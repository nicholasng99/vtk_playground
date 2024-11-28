#include "ModelViewer.hpp"

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNew.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkTransform.h>
#include <vtkAssembly.h>

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QtGui/QGuiApplication>
#include <QtGui/QSurfaceFormat>

#include <QVTKRenderWindowAdapter.h>

vtkStandardNewMacro(ModelViewer::Data);

ModelViewer::ModelViewer()
{
}

QQuickVTKItem::vtkUserData ModelViewer::initializeVTK(vtkRenderWindow *renderWindow)
{
    vtkNew<Data> vtk;

    vtkNew<vtkConeSource> cone;

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cone->GetOutputPort());
    vtk->actor->SetMapper(mapper);

    vtk->renderer->AddActor(vtk->actor);
    vtk->renderer->ResetCamera();
    vtk->renderer->SetBackground(0.0, 1.0, 1.0);
    vtk->renderer->SetBackground2(1.0, 0.0, 0.0);
    vtk->renderer->SetGradientBackground(true);

    renderWindow->AddRenderer(vtk->renderer);
    // renderWindow->SetMultiSamples(16);

    return vtk;
}

void ModelViewer::destroyingVTK(vtkRenderWindow *renderWindow, vtkUserData userData)
{
    qDebug() << "destroyed";
}

double ModelViewer::value() const
{
    return 0;
}

void ModelViewer::setValue(double value)
{
    dispatch_async([this, value](vtkRenderWindow *renderWindow, vtkUserData userData)
                   {
        auto* vtk = Data::SafeDownCast(userData);
        vtkNew<vtkTransform> transform;
        transform->Translate(0, 0, value);
        vtk->actor->SetUserTransform(transform);
        scheduleRender(); });
}