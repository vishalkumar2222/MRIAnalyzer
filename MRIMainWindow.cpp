#include "MRIMainWindow.h"
#include "ui_MRIMainWindow.h"

MRIMainWindow::MRIMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MRIMainWindow)
{
    ui->setupUi(this);

    vtk_renderer_ = new VTKRenderer(this);
    xy_slice_viewer_ = new SliceView("XY", this);
    yz_slice_viewer_ = new SliceView("YZ", this);
    xz_slice_viewer_ = new SliceView("ZX",this);

    ui->gridLayout->addWidget(xy_slice_viewer_, 0, 0);
    ui->gridLayout->addWidget(vtk_renderer_, 0, 1);
    ui->gridLayout->addWidget(yz_slice_viewer_, 1, 0);
    ui->gridLayout->addWidget(xz_slice_viewer_, 1, 1);

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

        vtk_renderer_->GetRenderer()->AddActor(actor);
        vtk_renderer_->UpdateRenderer();
    }
}

void MRIMainWindow::OnImportImageStackFileActionTriggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open"), tr("/"), tr("Image File(*.nii)"));

    vtkSmartPointer<vtkNIFTIImageReader> reader =
            vtkSmartPointer<vtkNIFTIImageReader>::New();

    reader->SetFileName(file_name.toStdString().c_str());
    reader->Update();

    if (reader->GetErrorCode() != vtkErrorCode::NoError)
    {
        qDebug()<<"Error in reading";
        return;
    }






    //    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    //            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //    vtkSmartPointer<vtkInteractorStyleImage> style =
    //            vtkSmartPointer<vtkInteractorStyleImage>::New();
    //    style->SetInteractionModeToImage3D();
    //    vtkSmartPointer<vtkRenderWindow> renWin =
    //            vtkSmartPointer<vtkRenderWindow>::New();
    //    iren->SetRenderWindow(renWin);
    //    iren->SetInteractorStyle(style);

    vtkSmartPointer<vtkMatrix4x4> matrix =
            vtkSmartPointer<vtkMatrix4x4>::New();
    if (reader->GetQFormMatrix())
    {
        matrix->DeepCopy(reader->GetQFormMatrix());
        matrix->Invert();
    }
    else if (reader->GetSFormMatrix())
    {
        matrix->DeepCopy(reader->GetSFormMatrix());
        matrix->Invert();
    }

    vtkSmartPointer<vtkImageReslice> reslice =
            vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetResliceAxes(matrix);
    reslice->SetInterpolationModeToLinear();
    reslice->Update();

    double range[2];
    int extent[6];
    reslice->GetOutput()->GetScalarRange(range);
    reslice->GetOutput()->GetExtent(extent);

    // check if image is 2D
    bool imageIs3D = (extent[5] > extent[4]);

    for (int i = 2*(imageIs3D == 0); i < 3; i++)
    {
        vtkSmartPointer<vtkImageSliceMapper> imageMapper =
                vtkSmartPointer<vtkImageSliceMapper>::New();
        if (i < 3)
        {
            imageMapper->SetInputConnection(reslice->GetOutputPort());
        }
        imageMapper->SetOrientation(i % 3);
        imageMapper->SliceAtFocalPointOn();

        vtkSmartPointer<vtkImageSlice> image =
                vtkSmartPointer<vtkImageSlice>::New();
        image->SetMapper(imageMapper);

        image->GetProperty()->SetColorWindow(range[1] - range[0]);
        image->GetProperty()->SetColorLevel(0.5*(range[0] + range[1]));
        image->GetProperty()->SetInterpolationTypeToNearest();


        switch(i)
        {
        case 0:
            xy_slice_viewer_->GetRenderer()->AddViewProp(image);
            break;
        case 1:
            yz_slice_viewer_->GetRenderer()->AddViewProp(image);
            break;
        case 2:
            xz_slice_viewer_->GetRenderer()->AddViewProp(image);
            break;
        }
    }

    xy_slice_viewer_->UpdateRenderer();
    yz_slice_viewer_->UpdateRenderer();
    xz_slice_viewer_->UpdateRenderer();






    // vtkSmartPointer<vtkImageDataToUniformGrid> image_to_grid = vtkSmartPointer<vtkImageDataToUniformGrid>::New();
    // image_to_grid->SetInputConnection(reader->GetOutputPort());
    // image_to_grid->Update();


    // vtkImageData *image_data = reader->GetOutput();

    //  vtkSmartPointer<vtkUniformGrid> uniform_grid = vtkSmartPointer<vtkUniformGrid>::New();


    // Convert the image to a polydata
    //    vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter =
    //      vtkSmartPointer<vtkImageDataGeometryFilter>::New();
    //    imageDataGeometryFilter->SetInputConnection(reader->GetOutputPort());
    //    imageDataGeometryFilter->Update();

    //    vtkSmartPointer<vtkPolyDataMapper> mapper =
    //      vtkSmartPointer<vtkPolyDataMapper>::New();
    //    mapper->SetInputConnection(imageDataGeometryFilter->GetOutputPort());

    //    vtkSmartPointer<vtkActor> actor =
    //      vtkSmartPointer<vtkActor>::New();
    //    actor->SetMapper(mapper);
    //    actor->GetProperty()->SetOpacity(0.5);

    //    uni
    //    uniform_grid->CopyAndCastFrom(image_data, image_data->);


    //    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();

    //    viewer->SetInputConnection(reader->GetOutputPort());

    //    viewer->Render();


    //    vtkSmartPointer<vtkImageActor> actor =vtkSmartPointer<vtkImageActor>::New();
    //    actor->SetInputData(reader->GetOutput());

    //    renderer_->AddActor(actor);
    //    renderer_->SetBackground(0.5,0.5,0.5);
    //    renderer_->ResetCamera();
    //    renderer_->Render();


}

void MRIMainWindow::on_action_Import_Data_triggered()
{
    ImportDialog dialog;

    dialog.exec();
}
