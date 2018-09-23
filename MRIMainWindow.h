#ifndef MRIMAINWINDOW_H
#define MRIMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <vtkSmartPointer.h>
#include <vtkImageMapper.h>
#include <vtkActor.h>
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
#include <vtkUniformGrid.h>
#include <vtkImageDataToUniformGrid.h>
#include <vtkUniformGridAMR.h>
#include <QDebug>
#include <vtkImageDataGeometryFilter.h>
#include <vtkProperty.h>
#include <vtkImageReslice.h>
#include <vtkImageSlice.h>
#include <vtkCamera.h>
#include <vtkErrorCode.h>
#include <vtkInteractorStyleImage.h>
#include <vtkUnsignedCharArray.h>
#include <vtkMatrix4x4.h>
#include <vtkImageViewer2.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkImageProperty.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMolecule.h>
#include "VTKRenderer.h"
#include "ImportDialog.h"
#include "AnimationWidget.h"
#include "ParticleMapper.h"
#include "ProjectTreeModel.h"
#include <QTimer>


#include <vtkPriorityQueue.h>
#include <vtkScalarBarActor.h>
#include <vtkSampleFunction.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include <vtkImageShiftScale.h>
#include <vtkLookupTable.h>
#include <vtkDoubleArray.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>
#include <vtkSmartVolumeMapper.h>
#include <QVector3D>
#include <QMultiHash>
#include <algorithm>
#include <vtkOggTheoraWriter.h>

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

    void on_action_Import_Data_triggered();

    void PlayAnimation();

    void on_action_Slice_View_triggered();

    void on_action_3D_View_triggered();

private:

    void ReadImageData(const QString& filename);
    void ReadMeshData(const QString& filename);

    void SplitMeshFile(const vtkSmartPointer<vtkPolyData> &source, vtkSmartPointer<vtkPolyData> &mesh);

    Ui::MRIMainWindow *ui;
    VTKRenderer *vtk_renderer_;
    QTimer *timer_;
    AnimationWidget *animate_widget_;

    ProjectTreeModel *project_model_;

    TreeItem *root_item_;
    TreeItem *image_Stack_item_;
    TreeItem *mesh_item_;

    int red;
    int green;
    int blue;

    QMap<QString, vtkProp3D*> actor_map_;

    QMultiHash<float, QVector3D> hash_;

    QList<float> activation_time_;

    double center_[3];

    bool center_set_;

    vtkIdType count_;

    vtkSmartPointer<vtkActor> animation_actor_;

    vtkSmartPointer<vtkPolyDataMapper> animation_mapper_;

};

#endif // MRIMAINWINDOW_H
