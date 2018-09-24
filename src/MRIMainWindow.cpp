#include "MRIMainWindow.h"
#include "ui_MRIMainWindow.h"
#include "TreeItem.h"

#include <vtkCellData.h>

MRIMainWindow::MRIMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MRIMainWindow)
{
    ui->setupUi(this);

    red = 0;
    green = 0;
    blue =0;
    center_set_ = false;

    count_ = 0;

    vtk_renderer_ = new VTKRenderer(this);
    animate_widget_ = new AnimationWidget(this);
    timer_ = new QTimer(this);



    QString style="QTreeView::branch:has-siblings:!adjoins-item {"
                  "border-image: url(:/images/vline.png) 0;"
                  "}"

                  "QTreeView::branch:has-siblings:adjoins-item {"
                  "border-image: url(:/images/branch-more.png) 0;"
                  "}"

                  "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
                  "border-image: url(:/images/branch-end.png) 0;"
                  " }"

                  "QTreeView::branch:has-children:!has-siblings:closed,"
                  " QTreeView::branch:closed:has-children:has-siblings {"
                  "border-image: none;"
                  "image: url(:/images/plus.png);"
                  "}"

                  "QTreeView::branch:open:has-children:!has-siblings,"
                  " QTreeView::branch:open:has-children:has-siblings  {"
                  "border-image: none;"
                  "image: url(:/images/minus.png);"
                  "}";
    ui->treeView->setStyleSheet(style);


    root_item_ = new TreeItem("Workspace");

    image_Stack_item_ = new TreeItem("Image Stack", root_item_);
    root_item_->appendChild(image_Stack_item_);


    mesh_item_ = new TreeItem("Mesh", root_item_);
    root_item_->appendChild(mesh_item_);

    animation_actor_ = vtkSmartPointer<vtkActor>::New();

    animation_mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();


    project_model_ = new ProjectTreeModel(this);
    project_model_->SetRootEntity(root_item_);
    ui->treeView->setModel(project_model_);
    ui->treeView->expandAll();

    ui->verticalLayout_main->addWidget(vtk_renderer_);
    ui->verticalLayout_main->addWidget(animate_widget_);

    connect(timer_,SIGNAL(timeout()),this,SLOT(PlayAnimation()));
    connect(animate_widget_,&AnimationWidget::StopButtonClicked,[this](){
        timer_->stop();
        animate_widget_->AnimationStatus(false);
        count_ = 0;
    });
    connect(animate_widget_,&AnimationWidget::PlayButtonClicked,[this](){
        timer_->start(200);
        animate_widget_->AnimationStatus(true);
    });

    connect(project_model_,&ProjectTreeModel::VisibilityChanged,[this](const QString& name, bool visibility){
        vtkProp3D *actor = actor_map_.value(name);
        actor->SetVisibility(visibility);
        vtk_renderer_->UpdateRenderer();
    });

}

MRIMainWindow::~MRIMainWindow()
{
    delete ui;
}

void MRIMainWindow::on_action_Import_Data_triggered()
{
    ImportDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        QStringList files = dialog.GetFiles();

        for(auto file : files)
        {
            QFileInfo info(file);
            if(info.suffix() == "vtk")
            {

                ReadMeshData(file);
            }
            else if(info.suffix() == "nii")
            {
                ReadImageData(file);
            }
        }
        project_model_->SetRootEntity(root_item_);
        ui->treeView->expandAll();
    }
}

void MRIMainWindow::PlayAnimation()
{
    if(activation_time_.count() == 0)
    {
        timer_->stop();
        animate_widget_->AnimationStatus(false);
        count_ = 0;
    }

    if(count_ >= activation_time_.count())
    {
        count_ = 0;
    }

    const auto& points = hash_.values(activation_time_[count_]);

    vtkSmartPointer<vtkCellArray> polys_cell= vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPoints> polys_points =vtkSmartPointer<vtkPoints>::New();


    for(const auto& point : points)
    {
        vtkIdType types[1];
        types[0] = polys_points->InsertNextPoint(point.x(), point.y(), point.z());
        polys_cell->InsertNextCell(1, types);
    }

    vtkSmartPointer<vtkPolyData> poly_data = vtkSmartPointer<vtkPolyData>::New();

    poly_data->SetPoints(polys_points);

    poly_data->SetVerts(polys_cell);

    animation_mapper_->SetInputData(poly_data);

    animation_actor_->SetMapper(animation_mapper_);

    animation_actor_->GetProperty()->SetColor(0.0, 1.0, 0.0);

    animation_actor_->GetProperty()->SetPointSize(5.0);

   // animation_actor_->GetProperty()->SetRenderPointsAsSpheres(true);

    vtk_renderer_->GetRenderer()->AddActor(animation_actor_);

    vtk_renderer_->UpdateRendererWidget();

    ++count_;
}

void MRIMainWindow::ReadImageData(const QString &filename)
{
    vtkSmartPointer<vtkNIFTIImageReader> reader =
            vtkSmartPointer<vtkNIFTIImageReader>::New();

    reader->SetFileName(filename.toStdString().c_str());
    reader->Update();

    if (reader->GetErrorCode() != vtkErrorCode::NoError)
    {
        qDebug()<<"Error in reading";
        return;
    }

    vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    mapper->SetInputData(reader->GetOutput());

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


    QFileInfo info(filename);
    TreeItem *item = new TreeItem(info.baseName(), image_Stack_item_, true);
    image_Stack_item_->appendChild(item);

    actor_map_.insert(info.baseName(), volume);

    vtk_renderer_->GetRenderer()->AddViewProp(volume);
    vtk_renderer_->UpdateRenderer();
}

void MRIMainWindow::ReadMeshData(const QString &filename)
{
    // Get all data from the file
    vtkSmartPointer<vtkGenericDataObjectReader> reader =
            vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(filename.toStdString().c_str());
    reader->Update();

    // All of the standard data types can be checked and obtained like this:
    if(reader->IsFilePolyData())
    {

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

        if(reader->GetPolyDataOutput()->GetNumberOfVerts() > 0)
        {
            vtkSmartPointer<vtkPolyData> mesh_poly_data = vtkSmartPointer<vtkPolyData>::New();

            this->SplitMeshFile(reader->GetPolyDataOutput(), mesh_poly_data);

            mapper->SetInputData(mesh_poly_data);
        }
        else
        {
            vtkSmartPointer<vtkPolyData> poly_data = vtkSmartPointer<vtkPolyData>::New();
            poly_data->DeepCopy(reader->GetPolyDataOutput());

            mapper->SetInputData(poly_data);
        }

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        actor->GetProperty()->SetColor(0.0,0.0,1.0);

        QFileInfo info(filename);

        TreeItem *item = new TreeItem(info.baseName(), mesh_item_, true);
        mesh_item_->appendChild(item);

        actor_map_.insert(info.baseName(), actor);

        vtk_renderer_->GetRenderer()->AddActor(actor);
        // vtk_renderer_->GetRenderer()->AddActor(point_actor);
        // vtk_renderer_->GetRenderer()->AddActor2D(scalarBar);
        vtk_renderer_->UpdateRenderer();
    }
}

void MRIMainWindow::SplitMeshFile(const vtkSmartPointer<vtkPolyData>& source, vtkSmartPointer<vtkPolyData>& mesh)
{

    hash_.clear();
    activation_time_.clear();

    vtkDataArray *scalers = source->GetCellData()->GetScalars();

    vtkSmartPointer<vtkCellArray> polys_cell= vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPoints> polys_points =vtkSmartPointer<vtkPoints>::New();


    vtkSmartPointer<vtkUnsignedCharArray> colors =
            vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");

    for(vtkIdType id = 0; id<source->GetNumberOfCells(); id++)
    {
        vtkCell *cell = source->GetCell(id);
        vtkPoints *points = cell->GetPoints();

        if(cell->GetCellType() == VTK_VERTEX)
        {
            double point[3] = {0.0,0.0,0.0};
            points->GetPoint(0,point);

            hash_.insert(scalers->GetTuple1(id), QVector3D(point[0],point[1],point[2]));
        }
        else if(cell->GetCellType() == VTK_TRIANGLE)
        {
            double point1[3] = {0.0,0.0,0.0};
            points->GetPoint(0,point1);
            double point2[3] = {0.0,0.0,0.0};
            points->GetPoint(1,point2);
            double point3[3] = {0.0,0.0,0.0};
            points->GetPoint(2,point3);

            vtkIdType types[3];
            types[0] = polys_points->InsertNextPoint(point1);
            types[1] = polys_points->InsertNextPoint(point2);
            types[2] = polys_points->InsertNextPoint(point3);
            polys_cell->InsertNextCell(3, types);
            unsigned char tempColor[3] = {red,
                                          green,
                                          blue};

            colors->InsertNextTypedTuple(tempColor);

            red += 2;
            green += 3;
            blue += 1 ;

            if(red >= 255)
            {
                red = 0;
            }
            if (green >= 255) {
                green = 0;
            }
            if(blue >= 255)
            {
                blue = 0;
            }
        }

    }

    mesh->SetPoints(polys_points);
    mesh->SetPolys(polys_cell);
    //   mesh->GetCellData()->SetScalars(colors);

    activation_time_ = hash_.uniqueKeys();

    std::sort(activation_time_.begin(), activation_time_.end());

}

void MRIMainWindow::on_action_Slice_View_triggered()
{
    vtk_renderer_->ChangeModeTo2DImage();
    vtk_renderer_->UpdateRenderer();
}

void MRIMainWindow::on_action_3D_View_triggered()
{
    vtk_renderer_->ChangeModeTo3D();
    vtk_renderer_->UpdateRenderer();
}
