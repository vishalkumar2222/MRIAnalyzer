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
#include <QFileDialog>
#include <vtkProperty.h>
#include <QDebug>

#include <vtkCamera.h>
#include <vtkErrorCode.h>
#include <vtkStructuredPoints.h>
#include "VTKRenderer.h"
#include "AnimationWidget.h"
#include "ParticleMapper.h"
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
#include <vtkCornerAnnotation.h>

class ColorDialog;

class RendererTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    RendererTabWidget(QWidget *parent = nullptr);

    void AddImageStack(const QString& name);

    void AddMesh(const QString& name);

    void StartAnimation(const int time = 100);

    void PauseAnimation();

    void RecordButtonClicked();

    void ChangeMinMaxColorActionTriggered();

    void StopButtonClicked();

    void UpdateRenderer();

    void ResetCamera();

    void SetBackgroundColorTriggered();

    void ClearAllData();

signals:
    void WriteLogs(QString log);

public slots:
    void SetActorVisibility(const QString& name, bool visibility = true);

    void ShowScar();

    void ShowInterpolatedActivationTime();

    void ShowImageInterpolation();

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

    bool is_paused_;

    vtkSmartPointer<vtkActor> animation_actor_;

    vtkSmartPointer<vtkCornerAnnotation> annotation_;

    vtkSmartPointer<vtkActor> mesh_actor_;

    vtkSmartPointer<vtkScalarBarActor> scalarBar;

    vtkSmartPointer<vtkPolyDataMapper> animation_mapper_;

    vtkSmartPointer<vtkPolyDataMapper> mesh_data_mapper_;

    vtkSmartPointer<ParticleMapper> particle_mapper_;

    vtkSmartPointer<vtkPointLocator> point_locator_;

    vtkSmartPointer<vtkPolyData> point_poly_data_;

    vtkSmartPointer<vtkLookupTable> lookup_table_;

    QString image_directory_;

//    vtkActor* mesh_actor_;
    QMap<QString, vtkProp3D*> actor_map_;
    QWidget *renderer_widget_;
    VTKRenderer *renderer_;
    SliceView *image_viewer_;
    QTimer *timer_;
    int image_count_;
    int activation_index_;
};

#endif // RENDERERTABWIDGET_H
