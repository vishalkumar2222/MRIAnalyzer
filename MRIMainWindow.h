#ifndef MRIMAINWINDOW_H
#define MRIMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <vtkNrrdReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper.h>
#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkNIFTIImageReader.h>
#include <vtkImageCast.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkVolumeProperty.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkImageSlice.h>
#include <vtkCubeSource.h>
#include <QVTKOpenGLWidget.h>
#include <vtkUniformGrid.h>
#include <vtkImageDataToUniformGrid.h>
#include <vtkUniformGridAMR.h>
#include <QDebug>
#include <vtkImageDataGeometryFilter.h>
#include <vtkProperty.h>
#include <vtkImageViewer2.h>

namespace Ui {
class MRIMainWindow;
}

class MRIMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MRIMainWindow(QWidget *parent = 0);
    ~MRIMainWindow();

private slots:

    void OnImportMeshFileActionTriggered();

    void OnImportImageStackFileActionTriggered();

private:
    Ui::MRIMainWindow *ui;
    QVTKOpenGLWidget *widget_;
    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
};

#endif // MRIMAINWINDOW_H
