#include "MRIMainWindow.h"
#include "ui_MRIMainWindow.h"

MRIMainWindow::MRIMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MRIMainWindow)
{
    ui->setupUi(this);

    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    render_window_->AddRenderer(renderer_.Get());
    widget_ = new QVTKOpenGLWidget();
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    renderer_->SetBackground(0.5,0.5,0.5);
    this->setCentralWidget(widget_);
    QObject::connect(ui->action_Image_Stack_nrrd,&QAction::triggered, this, &MRIMainWindow::OnImportImageStackFileActionTriggered);
    QObject::connect(ui->action_Mesh_File_vtk,&QAction::triggered, this, &MRIMainWindow::OnImportMeshFileActionTriggered);

    ui->toolBar->addActions(QList<QAction*>()<<ui->actionNew <<ui->action_Open<<ui->action_Save);
}

MRIMainWindow::~MRIMainWindow()
{
    delete ui;
}

void MRIMainWindow::OnImportMeshFileActionTriggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open"), tr("/"), tr("Mesh File(*.vtk)"));
    if(file_name.isEmpty())
        return;

    // Get all data from the file
    vtkSmartPointer<vtkGenericDataObjectReader> reader =
            vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(file_name.toStdString().c_str());
    reader->Update();

    // All of the standard data types can be checked and obtained like this:
    if(reader->IsFilePolyData())
    {
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(reader->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

        actor->SetMapper(mapper);

        renderer_->AddActor(actor);
        renderer_->ResetCamera();
        renderer_->Render();
    }

}

void MRIMainWindow::OnImportImageStackFileActionTriggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open"), tr("/"), tr("Image File(*.nii)"));

    vtkSmartPointer<vtkNIFTIImageReader> reader =
          vtkSmartPointer<vtkNIFTIImageReader>::New();

    reader->SetFileName(file_name.toStdString().c_str());
    reader->Update();

   // vtkSmartPointer<vtkImageDataToUniformGrid> image_to_grid = vtkSmartPointer<vtkImageDataToUniformGrid>::New();
   // image_to_grid->SetInputConnection(reader->GetOutputPort());
   // image_to_grid->Update();


   // vtkImageData *image_data = reader->GetOutput();

  //  vtkSmartPointer<vtkUniformGrid> uniform_grid = vtkSmartPointer<vtkUniformGrid>::New();


    // Convert the image to a polydata
    vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter =
      vtkSmartPointer<vtkImageDataGeometryFilter>::New();
    imageDataGeometryFilter->SetInputConnection(reader->GetOutputPort());
    imageDataGeometryFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(imageDataGeometryFilter->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetOpacity(0.5);

//    uni
//    uniform_grid->CopyAndCastFrom(image_data, image_data->);


//    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();

//    viewer->SetInputConnection(reader->GetOutputPort());

//    viewer->Render();


//    vtkSmartPointer<vtkImageActor> actor =vtkSmartPointer<vtkImageActor>::New();
//    actor->SetInputData(reader->GetOutput());

    renderer_->AddActor(actor);
    renderer_->SetBackground(0.5,0.5,0.5);
    renderer_->ResetCamera();
    renderer_->Render();
}
