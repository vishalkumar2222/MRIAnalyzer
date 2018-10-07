#ifndef VTKRENDERER_H
#define VTKRENDERER_H

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>

namespace Ui {
class VTKRenderer;
}

class VTKRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit VTKRenderer(QWidget *parent = 0);
    ~VTKRenderer();

    vtkSmartPointer<vtkRenderer> GetRenderer() const;

    void ChangeModeTo3D();

    void ChangeModeTo2DImage();

    void UpdateRenderer();

    void UpdateRendererWidget();

    void ResetCamera();
    void ChangeCameraToBackView();
    void ChangeCameraToFrontView();
    void ChangeCameraToRightView();
    void ChangeCameraToLeftView();
    void ChangeCameraToBottomView();
    void ChangeCameraToTopView();
private:
    Ui::VTKRenderer *ui;
    QVTKOpenGLWidget *widget_;
    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
    vtkSmartPointer<vtkInteractorStyleImage> image_style_interactor_;
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> track_ball_interactor_style_;
};

#endif // VTKRENDERER_H
