#ifndef VTKRENDERER_H
#define VTKRENDERER_H

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

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

    void UpdateRenderer();

private:
    Ui::VTKRenderer *ui;
    QVTKOpenGLWidget *widget_;
    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
};

#endif // VTKRENDERER_H
