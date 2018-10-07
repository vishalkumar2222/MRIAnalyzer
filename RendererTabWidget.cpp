#include "RendererTabWidget.h"

RendererTabWidget::RendererTabWidget(QWidget *parent)
    :QTabWidget(parent)
{

    renderer_ = new VTKRenderer();
    image_viewer_ = new SliceView();
    this->addTab(renderer_, "3D Mode");


    red = 0;
    green = 0;
    blue =0;
    center_set_ = false;

    is_recording_ = false;

    time_elapsed_ = 0.0f;

    timer_ = new QTimer(this);

    connect(timer_,&QTimer::timeout,[this](){
        this->PlayAnimation();
    });


    animation_actor_ = vtkSmartPointer<vtkActor>::New();

    animation_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();

    point_poly_data_ = vtkSmartPointer<vtkPolyData>::New();

    point_locator_ = vtkSmartPointer<vtkPointLocator>::New();

}

void RendererTabWidget::Set3DMode()
{
    this->removeTab(0);
    this->addTab(renderer_, "3D Mode");
}

void RendererTabWidget::SetSliceMode()
{
    this->removeTab(0);
    this->addTab(image_viewer_, "2D Mode");
    image_viewer_->GetImageViewer()->Render();
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
    //  volumeProperty->SetColor(color);

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
}

void RendererTabWidget::AddMesh(const QString &name)
{
    vtkSmartPointer<vtkBandedPolyDataContourFilter> banded_contour = vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
    banded_contour->SetInputData(RendererData::Get()->GetMeshData());
    banded_contour->SetScalarModeToValue();
    banded_contour->Update();

    //    double range[2];
    //    RendererData::Get()->GetMeshData()->GetScalarRange(range);
    //    banded_contour->GenerateValues(10, range[0], range[1]);

    //    vtkSmartPointer<vtkLookupTable> lookup_table_ = vtkSmartPointer<vtkLookupTable>::New();

    //    lookup_table_->SetTableRange(range[0], range[1]);
    //    lookup_table_->SetHueRange(.667, 0);
    //    lookup_table_->SetSaturationRange(1, 1);
    //    lookup_table_->SetValueRange(1, 1);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(banded_contour->GetOutputPort());

    vtkSmartPointer<vtkScalarBarActor> scalarBar =
            vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(mapper->GetLookupTable());
    scalarBar->SetTitle("Scar");
    scalarBar->SetNumberOfLabels(10);
    scalarBar->SetOrientationToVertical();
    scalarBar->SetMaximumWidthInPixels(100);


    //   mapper->SetInputData(RendererData::Get()->GetMeshData());
    // mapper->SetScalarModeToUsePointData();
    // mapper->SetLookupTable(lookup_table_);

    // The labeled data mapper will place labels at the points
    //    vtkSmartPointer<vtkLabeledDataMapper> labelMapper =
    //            vtkSmartPointer<vtkLabeledDataMapper>::New();
    //    labelMapper->SetFieldDataName("scar");
    //    labelMapper->SetInputData(RendererData::Get()->GetMeshData());
    //   // labelMapper->SetLabelModeToLabelScalars();
    //    labelMapper->SetLabelFormat("%6.2f");

    //    vtkSmartPointer<vtkActor2D> isolabels =
    //            vtkSmartPointer<vtkActor2D>::New();
    //    isolabels->SetMapper(labelMapper);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    actor_map_.insert(name, actor);

    renderer_->GetRenderer()->AddActor(actor);
    renderer_->GetRenderer()->AddActor(scalarBar);
    renderer_->UpdateRenderer();
}

void RendererTabWidget::StartAnimation()
{
    time_elapsed_ = 0.0f;
    image_count_ = 0;
    timer_->start(500);
    QDir::current().mkdir("temp");
    image_directory_ = QDir::currentPath() + "/temp/";

    QDir dir(image_directory_);
    auto file_infos = dir.entryInfoList(QStringList() << "*.png",QDir::Files);
    for(auto info : file_infos){
        QFile file(info.absoluteFilePath());
        file.remove();
    }

    emit WriteLogs("Animation Started");
}

void RendererTabWidget::RecordButtonClicked()
{
    is_recording_ = true;
    emit WriteLogs("Recording...");
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

        }
    }
    is_recording_ = false;
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

    QColor new_color  = QColorDialog::getColor(color,this,tr("Choose Color"));

    renderer_->GetRenderer()->SetBackground(new_color.redF(), new_color.greenF() ,new_color.blueF());
    renderer_->GetRenderer()->SetBackgroundAlpha(new_color.alphaF());
    renderer_->UpdateRendererWidget();


}

void RendererTabWidget::PlayAnimation()
{

    if(RendererData::Get()->GetActivationTime().count() == 0)
    {
        timer_->stop();
        time_elapsed_ = 0.0f;
    }

    if(time_elapsed_ >= RendererData::Get()->GetActivationTime().last())
    {
        time_elapsed_ = 0.0f;
    }

    vtkSmartPointer<vtkCellArray> polys_cell= vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPoints> polys_points =vtkSmartPointer<vtkPoints>::New();

    for(const double& time_elapsed : RendererData::Get()->GetActivationPointHash().keys())
    {
        if(time_elapsed <= time_elapsed_)
        {
            const auto& points = RendererData::Get()->GetActivationPointHash().values(time_elapsed);
            for(const auto& point : points)
            {
                vtkIdType types[1];
                types[0] = polys_points->InsertNextPoint(point.x(), point.y(), point.z());
                polys_cell->InsertNextCell(1, types);
            }
        }
    }

    vtkSmartPointer<vtkPolyData> poly_data = vtkSmartPointer<vtkPolyData>::New();

    poly_data->SetPoints(polys_points);

    poly_data->SetVerts(polys_cell);

    animation_mapper_->SetInputData(poly_data);

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

    animation_actor_->SetMapper(animation_mapper_);

    animation_actor_->GetProperty()->SetColor(0.0, 1.0, 0.0);

    animation_actor_->GetProperty()->SetPointSize(3.0);

    renderer_->GetRenderer()->AddActor(animation_actor_);

    renderer_->UpdateRendererWidget();

    time_elapsed_ = time_elapsed_ + 0.1;
}


void RendererTabWidget::SetActorVisibility(const QString &name, bool visibility)
{
    actor_map_.value(name)->SetVisibility(visibility);
    renderer_->UpdateRenderer();
}
