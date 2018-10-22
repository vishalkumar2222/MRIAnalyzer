#include "RendererTabWidget.h"
#include "ColorDialog.h"
#include <vtkPointInterpolator.h>
#include <vtkLinearKernel.h>
#include <vtkPolyDataWriter.h>
#include <vtkCellDataToPointData.h>
#include <vtkProbeFilter.h>

RendererTabWidget::RendererTabWidget(QWidget *parent)
    :QTabWidget(parent)
{

    renderer_ = new VTKRenderer();
    image_viewer_ = new SliceView();
    this->addTab(renderer_, "3D Mode");
    this->addTab(image_viewer_, "Image Viewer");


    red = 0;
    green = 0;
    blue =0;
    center_set_ = false;

    is_recording_ = false;
    is_paused_ = false;

    time_elapsed_ = 0.0f;
    activation_index_ = 0;

    timer_ = new QTimer(this);

    connect(timer_,&QTimer::timeout,[this](){
        this->PlayAnimation();
    });


    animation_actor_ = vtkSmartPointer<vtkActor>::New();

    animation_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();

    point_poly_data_ = vtkSmartPointer<vtkPolyData>::New();

    point_locator_ = vtkSmartPointer<vtkPointLocator>::New();

    particle_mapper_ = vtkSmartPointer<ParticleMapper>::New();

    mesh_data_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();

    scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();

}

void RendererTabWidget::AddImageStack(const QString &name)
{
    vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    mapper->SetInputData(RendererData::Get()->GetImageData());

    //    vtkNew<vtkOpenGLGPUVolumeRayCastMapper> mapper;
    //    mapper->SetInputData(reader->GetOutput());
    //    mapper->SetUseJittering(1);

    vtkSmartPointer<vtkVolumeProperty> volumeProperty =
            vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->ShadeOff();
    volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);

    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
            vtkSmartPointer<vtkPiecewiseFunction>::New();
    compositeOpacity->AddPoint(0, 0.00);
    compositeOpacity->AddPoint(80, 0.029);
    compositeOpacity->AddPoint(112, 0.5);
    compositeOpacity->AddPoint(176, 0.85);
    compositeOpacity->AddPoint(255, 1.0);
    //  volumeProperty->SetScalarOpacity(compositeOpacity);

    vtkSmartPointer<vtkColorTransferFunction> color =
            vtkSmartPointer<vtkColorTransferFunction>::New();
    color->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
    color->AddRGBPoint(80.0, 0.55, 0.45, 0.39);
    color->AddRGBPoint(112.0, 0.51, 0.4, 0.36);
    color->AddRGBPoint(176.0, 0.78, 0.54, 0.3);
    color->AddRGBPoint(255.0, 0.9, 0.9, 0.9);
    // volumeProperty->SetColor(color);

    volumeProperty->ShadeOn();
    volumeProperty->SetDiffuse(0, 1);
    volumeProperty->SetAmbient(0, 0.6);
    volumeProperty->SetSpecular(0, 0.8);
    volumeProperty->SetSpecularPower(0, 50);

    vtkSmartPointer<vtkVolume> volume =
            vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(mapper);
    volume->SetProperty(volumeProperty);

    actor_map_.insert(name, volume);

    renderer_->GetRenderer()->AddViewProp(volume);
    renderer_->UpdateRenderer();


    //Image Viewer

    image_viewer_->GetImageViewer()->SetInputData(RendererData::Get()->GetImageData());
    image_viewer_->UpdateImageViewerInfo();
    image_viewer_->GetImageViewer()->SetSliceOrientationToXY();
    image_viewer_->GetImageViewer()->UpdateDisplayExtent();

    image_viewer_->GetSettingsInfo().level = image_viewer_->GetImageViewer()->GetColorLevel();
    image_viewer_->GetSettingsInfo().window = image_viewer_->GetImageViewer()->GetColorWindow();
    image_viewer_->GetSettingsInfo().plane = ImageViewer::orientation::kXY;
    image_viewer_->GetSettingsInfo().min_slice_ = image_viewer_->GetImageViewer()->GetSliceMin();
    image_viewer_->GetSettingsInfo().max_slice_ = image_viewer_->GetImageViewer()->GetSliceMax();
    image_viewer_->GetSettingsInfo().current_slice_ = image_viewer_->GetImageViewer()->GetSliceMin();

    image_viewer_->UpdateRenderer();

}


void RendererTabWidget::AddMesh(const QString &name)
{
    mesh_data_mapper_->SetInputData(RendererData::Get()->GetMeshData());
    mesh_data_mapper_->SetScalarVisibility(0);

    mesh_actor_ = vtkSmartPointer<vtkActor>::New();
    mesh_actor_->SetMapper(mesh_data_mapper_);

    actor_map_.insert(name, mesh_actor_);

    renderer_->GetRenderer()->AddActor(mesh_actor_);
    renderer_->UpdateRenderer();
}

void RendererTabWidget::StartAnimation(const int time)
{
    if(is_paused_)
    {
        timer_->start(time);
    }
    else
    {
        time_elapsed_ = 0.0f;
        image_count_ = 0;
        activation_index_ = 0;
        timer_->start(time);
        QDir::current().mkdir("temp");
        image_directory_ = QDir::currentPath() + "/temp/";

        QDir dir(image_directory_);
        auto file_infos = dir.entryInfoList(QStringList() << "*.png",QDir::Files);
        for(auto info : file_infos){
            QFile file(info.absoluteFilePath());
            file.remove();
        }

        renderer_->GetRenderer()->RemoveViewProp(annotation_);

        annotation_ = vtkSmartPointer<vtkCornerAnnotation>::New();

        renderer_->GetRenderer()->AddViewProp(annotation_);
    }

    emit WriteLogs("Animation Started");
}


void RendererTabWidget::PauseAnimation()
{
    timer_->stop();
    is_paused_ = true;
}

void RendererTabWidget::RecordButtonClicked()
{
    is_recording_ = true;
    emit WriteLogs("Recording...");
}

void RendererTabWidget::ChangeMinMaxColorActionTriggered()
{
    ColorDialog dialog;

    double *range = color_transfer_function_->GetRange();

    double *current_min_color = color_transfer_function_->GetColor(range[0]);
    QColor current_min;
    current_min.setRgbF(current_min_color[0], current_min_color[1], current_min_color[2]);
    dialog.SetMinColor(current_min);


    double *current_max_color = color_transfer_function_->GetColor(range[1]);
    QColor current_max;
    current_max.setRgbF(current_max_color[0], current_max_color[1], current_max_color[2]);

    dialog.SetMaxColor(current_max);

    if(dialog.exec() == QDialog::Accepted)
    {
        renderer_->GetRenderer()->RemoveActor(mesh_actor_);
        QString key = actor_map_.key(mesh_actor_);
        actor_map_.remove(key);

        vtkSmartPointer<vtkBandedPolyDataContourFilter> banded_contour = vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
        banded_contour->SetInputData(RendererData::Get()->GetMeshData());
        banded_contour->SetScalarModeToValue();
        banded_contour->Update();

        mesh_data_mapper_->SetInputConnection(banded_contour->GetOutputPort());

        color_transfer_function_->AddRGBPoint(range[0], dialog.GetMinColor().redF(),dialog.GetMinColor().greenF(),dialog.GetMinColor().blueF());
        color_transfer_function_->AddRGBPoint(range[1], dialog.GetMaxColor().redF(),dialog.GetMaxColor().greenF(),dialog.GetMaxColor().blueF());
        color_transfer_function_->Build();
        mesh_data_mapper_->SetLookupTable(color_transfer_function_);

        mesh_actor_ = vtkSmartPointer<vtkActor>::New();
        mesh_actor_->SetMapper(mesh_data_mapper_);

        scalarBar->SetLookupTable(color_transfer_function_);

        actor_map_.insert(key,mesh_actor_);

        renderer_->GetRenderer()->AddActor(mesh_actor_);
        // renderer_->GetRenderer()->AddActor(scalarBar);
        renderer_->UpdateRenderer();
    }
}

void RendererTabWidget::StopButtonClicked()
{
    timer_->stop();
    time_elapsed_ = 0.0f;
    if(is_recording_)
    {
        QString filename = QFileDialog::getSaveFileName(this,tr("Filename"), QDir::rootPath(), tr("*.webm"));
        if(!filename.isEmpty())
        {
            AnimationSaveDialog *dialog = new AnimationSaveDialog(image_directory_,QStringList()<<"-framerate"<<"5"<<"-i"<<"image%d.png"<<filename, this);
            dialog->exec();
            emit WriteLogs("Saved");
        }
    }
    is_recording_ = false;
    is_paused_ = false;
    renderer_->GetRenderer()->RemoveActor(animation_actor_);
    renderer_->GetRenderer()->Render();
}

void RendererTabWidget::UpdateRenderer()
{
    renderer_->UpdateRendererWidget();
}

void RendererTabWidget::ResetCamera()
{
    renderer_->GetRenderer()->ResetCamera();
}

void RendererTabWidget::SetBackgroundColorTriggered()
{
    double *rawcolor = renderer_->GetRenderer()->GetBackground();

    QColor color;
    color.setRedF(rawcolor[0]);
    color.setGreenF(rawcolor[1]);
    color.setBlueF(rawcolor[2]);
    color.setAlphaF(renderer_->GetRenderer()->GetBackgroundAlpha());

    QColor new_color  = QColorDialog::getColor(color,this,tr("Choose Color"),QColorDialog::DontUseNativeDialog);

    renderer_->GetRenderer()->SetBackground(new_color.redF(), new_color.greenF() ,new_color.blueF());
    renderer_->GetRenderer()->SetBackgroundAlpha(new_color.alphaF());
    renderer_->UpdateRendererWidget();


}

void RendererTabWidget::ClearAllData()
{
    renderer_->GetRenderer()->RemoveAllViewProps();
    actor_map_.clear();
}

void RendererTabWidget::PlayAnimation()
{

    if(RendererData::Get()->GetActivationTime().count() == activation_index_)
    {
        activation_index_ = 0;
    }

    vtkSmartPointer<vtkCellArray> polys_cell= vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPoints> polys_points =vtkSmartPointer<vtkPoints>::New();

    const auto& activation_list = RendererData::Get()->GetActivationPointHash().keys();

    annotation_->SetText(1, std::to_string(activation_list[activation_index_]).c_str());

    const auto& points = RendererData::Get()->GetActivationPointHash().values(activation_list[activation_index_]);
    for(const auto& point : points)
    {
        vtkIdType types[1];
        types[0] = polys_points->InsertNextPoint(point.x(), point.y(), point.z());
        polys_cell->InsertNextCell(1, types);
    }


    vtkSmartPointer<vtkPolyData> poly_data = vtkSmartPointer<vtkPolyData>::New();

    poly_data->SetPoints(polys_points);

    poly_data->SetVerts(polys_cell);

    //  animation_mapper_->SetInputData(poly_data);

    particle_mapper_->SetInputData(poly_data);

    if(is_recording_)
    {
        vtkSmartPointer<vtkWindowToImageFilter> window_to_image_filter =
                vtkSmartPointer<vtkWindowToImageFilter>::New();
        window_to_image_filter->SetInput(renderer_->GetRenderer()->GetRenderWindow());
        window_to_image_filter->SetInputBufferTypeToRGBA();
        window_to_image_filter->ReadFrontBufferOff();
        window_to_image_filter->Update();

        vtkSmartPointer<vtkPNGWriter> writter = vtkSmartPointer<vtkPNGWriter>::New();
        writter->SetInputConnection(window_to_image_filter->GetOutputPort());
        writter->SetFileName(QString(image_directory_ + QString::asprintf("image%d", image_count_) + ".png").toStdString().c_str());
        writter->Write();
        ++image_count_;

    }

    animation_actor_->SetMapper(particle_mapper_);

    // animation_actor_->GetProperty()->SetColor(0.0, 1.0, 0.0);

    // animation_actor_->GetProperty()->SetDiffuseColor(0.0,1.0,0.0);

    // animation_actor_->GetProperty()->SetPointSize(0.5);

    renderer_->GetRenderer()->AddActor(animation_actor_);

    renderer_->UpdateRendererWidget();

    ++activation_index_;
}


void RendererTabWidget::SetActorVisibility(const QString &name, bool visibility)
{
    actor_map_.value(name)->SetVisibility(visibility);
    renderer_->UpdateRenderer();
}


void RendererTabWidget::ShowScar()
{
    double *range = RendererData::Get()->GetMeshData()->GetPointData()->GetScalars()->GetRange();

    vtkSmartPointer<vtkBandedPolyDataContourFilter> banded_contour = vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
    banded_contour->SetInputData(RendererData::Get()->GetMeshData());
    banded_contour->SetScalarModeToValue();
    banded_contour->Update();

    mesh_data_mapper_->SetInputConnection(banded_contour->GetOutputPort());
    color_transfer_function_ = vtkSmartPointer<vtkColorTransferFunction>::New();
    color_transfer_function_->AddRGBPoint(range[0], 0.0,0.0,1.0);
    color_transfer_function_->AddRGBPoint(range[1], 1.0,0.0,0.0);
    color_transfer_function_->Build();

    mesh_data_mapper_->SetLookupTable(color_transfer_function_);
    mesh_data_mapper_->SetScalarRange(range);
    mesh_data_mapper_->SetScalarVisibility(1);

    scalarBar->SetLookupTable(color_transfer_function_);
    scalarBar->SetTitle("Scar");
    scalarBar->SetNumberOfLabels(10);
    scalarBar->SetOrientationToVertical();
    scalarBar->SetMaximumWidthInPixels(100);

    mesh_actor_->SetMapper(mesh_data_mapper_);
    mesh_actor_->GetProperty()->SetInterpolationToFlat();

    renderer_->GetRenderer()->AddActor(scalarBar);

    renderer_->UpdateRenderer();

}

void RendererTabWidget::ShowInterpolatedActivationTime()
{
    vtkSmartPointer<vtkCellDataToPointData> cell_point = vtkSmartPointer<vtkCellDataToPointData>::New();
    cell_point->SetInputData(RendererData::Get()->GetActivationData());
    vtkSmartPointer<vtkPointInterpolator> interpolator = vtkSmartPointer<vtkPointInterpolator>::New();
    interpolator->SetInputData(RendererData::Get()->GetMeshData());
    interpolator->SetSourceConnection(cell_point->GetOutputPort());

    vtkSmartPointer<vtkLinearKernel> kernel = vtkSmartPointer<vtkLinearKernel>::New();

    interpolator->SetKernel(kernel);

    interpolator->Update();


    color_transfer_function_ = vtkSmartPointer<vtkColorTransferFunction>::New();
    double *range = interpolator->GetOutput()->GetScalarRange();
    color_transfer_function_->AddRGBPoint(range[0], 0.0, 0.0, 1.0);
    color_transfer_function_->AddRGBPoint(range[1], 1.0, 0.0, 0.0);
    color_transfer_function_->Build();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(interpolator->GetOutputPort());
    mesh_data_mapper_->SetInputConnection(interpolator->GetOutputPort());
    // particle_mapper_->SetInputConnection(interpolator->GetOutputPort());

    mesh_data_mapper_->SetLookupTable(color_transfer_function_);
    mesh_data_mapper_->SetScalarRange(interpolator->GetOutput()->GetScalarRange());
    mesh_data_mapper_->SetScalarVisibility(1);

    scalarBar->SetLookupTable(color_transfer_function_);
    scalarBar->SetTitle("Activation Time");
    scalarBar->SetNumberOfLabels(10);
    scalarBar->SetOrientationToVertical();
    scalarBar->SetMaximumWidthInPixels(100);

    mesh_actor_->SetMapper(mesh_data_mapper_);

    renderer_->GetRenderer()->AddActor(scalarBar);

    renderer_->UpdateRenderer();
}

void RendererTabWidget::ShowImageInterpolation()
{
//    vtkSmartPointer<vtkCellDataToPointData> cell_point = vtkSmartPointer<vtkCellDataToPointData>::New();
//    cell_point->SetInputData(RendererData::Get()->GetActivationData());

//    vtkSmartPointer<vtkProbeFilter> probe =
//      vtkSmartPointer<vtkProbeFilter>::New();

//    probe->SetSourceData(RendererData::Get()->GetImageData());
//    probe->SetInputData(cell_point->GetOutput());

//    probe->Update();

//    image_viewer_->GetImageViewer()->SetInputData(vtkImageData::SafeDownCast(probe->GetOutput()));
//    image_viewer_->UpdateImageViewerInfo();
//    image_viewer_->GetImageViewer()->SetSliceOrientationToXY();
//    image_viewer_->GetImageViewer()->UpdateDisplayExtent();

//    image_viewer_->GetSettingsInfo().level = image_viewer_->GetImageViewer()->GetColorLevel();
//    image_viewer_->GetSettingsInfo().window = image_viewer_->GetImageViewer()->GetColorWindow();
//    image_viewer_->GetSettingsInfo().plane = ImageViewer::orientation::kXY;

//    image_viewer_->UpdateRenderer();
}
