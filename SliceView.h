#ifndef SLICEVIEW_H
#define SLICEVIEW_H

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include "SliceInteratorStyle.h"

class SliceInteratorStyle;

namespace Ui {
class SliceView;
}

class SliceView : public QWidget
{
    Q_OBJECT

public:
    explicit SliceView(const QString &name, QWidget *parent = 0);
    ~SliceView();

    void SetNumberOfSlices(int number);

    void SetCurrentSlice(int num);

    vtkSmartPointer<vtkRenderer> GetRenderer() const;

    void UpdateRenderer();

    vtkSmartPointer<vtkImageViewer2> GetImageViewer() const;

private:
    Ui::SliceView *ui;
    QVTKOpenGLWidget *widget_;
    vtkSmartPointer<vtkRenderer> renderer_;
    SliceInteratorStyle *image_interactor_style_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
    vtkSmartPointer<vtkImageViewer2> image_viewer_;
};

#endif // SLICEVIEW_H
