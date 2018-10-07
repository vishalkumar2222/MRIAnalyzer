#ifndef RENDERERTABWIDGET_H
#define RENDERERTABWIDGET_H

#include <QTabWidget>
#include "VTKRenderer.h"
#include "SliceView.h"

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
#include <vtkPointLocator.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkMarchingCubes.h>
#include <vtkPNGWriter.h>
#include <vtkLabeledDataMapper.h>
#include <vtkLabeledContourMapper.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <QDir>
#include "RendererData.h"
#include "AnimationSaveDialog.h"
#include <QFileInfoList>
#include <QFileInfo>
#include <QColorDialog>

class RendererTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    RendererTabWidget(QWidget *parent = nullptr);

    void Set3DMode();

    void SetSliceMode();

    void AddImageStack(const QString& name);

    void AddMesh(const QString& name);

    void StartAnimation();

    void RecordButtonClicked();

    void StopButtonClicked();

    void UpdateRenderer();

    void ResetCamera();

    void SetBackgroundColorTriggered();


signals:
    void WriteLogs(QString log);

public slots:
    void SetActorVisibility(const QString& name, bool visibility = true);

private:

    void PlayAnimation();

    int red;
    int green;
    int blue;

    double center_[3];

    bool center_set_;

    bool is_recording_;

    bool is_first_frame_;

    double time_elapsed_;

    vtkSmartPointer<vtkActor> animation_actor_;

    vtkSmartPointer<vtkPolyDataMapper> animation_mapper_;

    vtkSmartPointer<vtkPointLocator> point_locator_;

    vtkSmartPointer<vtkPolyData> point_poly_data_;

    QString image_directory_;

    QMap<QString, vtkProp3D*> actor_map_;
    QWidget *renderer_widget_;
    VTKRenderer *renderer_;
    SliceView *image_viewer_;
    QTimer *timer_;
    int image_count_;
};

#endif // RENDERERTABWIDGET_H
