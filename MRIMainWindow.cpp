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

    connect(ui->action_Mesh_View, &QAction::triggered, [this](bool checked){
        vtk_renderer_->setVisible(checked);
    });
    connect(ui->action_Image_Stack, &QAction::triggered, [this](bool checked){
        xy_slice_viewer_->setVisible(checked);
        yz_slice_viewer_->setVisible(checked);
        xz_slice_viewer_->setVisible(checked);
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
    }
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

//    vtkSmartPointer<vtkImageActor> image_actor = vtkSmartPointer<vtkImageActor>::New();

//    image_actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

    xy_slice_viewer_->GetImageViewer()->SetInputConnection(reader->GetOutputPort());
    xy_slice_viewer_->GetImageViewer()->SetSliceOrientationToXY();

    xy_slice_viewer_->UpdateRenderer();

//    vtkSmartPointer<vtkMatrix4x4> matrix =
//            vtkSmartPointer<vtkMatrix4x4>::New();
//    if (reader->GetQFormMatrix())
//    {
//        matrix->DeepCopy(reader->GetQFormMatrix());
//        matrix->Invert();
//    }
//    else if (reader->GetSFormMatrix())
//    {
//        matrix->DeepCopy(reader->GetSFormMatrix());
//        matrix->Invert();
//    }

//    vtkSmartPointer<vtkImageReslice> reslice =
//            vtkSmartPointer<vtkImageReslice>::New();
//    reslice->SetInputConnection(reader->GetOutputPort());
//    reslice->SetResliceAxes(matrix);
//    reslice->SetInterpolationModeToLinear();
//    reslice->Update();

//    double range[2];
//    int extent[6];
//    reslice->GetOutput()->GetScalarRange(range);
//    reslice->GetOutput()->GetExtent(extent);

//    // check if image is 2D
//    bool imageIs3D = (extent[5] > extent[4]);

//    for (int i = 2*(imageIs3D == 0); i < 3; i++)
//    {
//        vtkSmartPointer<vtkImageSliceMapper> imageMapper =
//                vtkSmartPointer<vtkImageSliceMapper>::New();
//        if (i < 3)
//        {
//            imageMapper->SetInputConnection(reslice->GetOutputPort());
//        }
//        imageMapper->SetOrientation(i % 3);
//        imageMapper->SliceAtFocalPointOn();

//        vtkSmartPointer<vtkImageSlice> image =
//                vtkSmartPointer<vtkImageSlice>::New();
//        image->SetMapper(imageMapper);

//        image->GetProperty()->SetColorWindow(range[1] - range[0]);
//        image->GetProperty()->SetColorLevel(0.5*(range[0] + range[1]));
//        image->GetProperty()->SetInterpolationTypeToNearest();


//        switch(i)
//        {
//        case 0:
//            xy_slice_viewer_->GetRenderer()->AddViewProp(image);
//            break;
//        case 1:
//            yz_slice_viewer_->GetRenderer()->AddViewProp(image);
//            break;
//        case 2:
//            xz_slice_viewer_->GetRenderer()->AddViewProp(image);
//            break;
//        }
//    }

//    xy_slice_viewer_->UpdateRenderer();
//    yz_slice_viewer_->UpdateRenderer();
//    xz_slice_viewer_->UpdateRenderer();
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
        mapper->SetInputConnection(reader->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

        actor->SetMapper(mapper);

        vtk_renderer_->GetRenderer()->AddActor(actor);
        vtk_renderer_->UpdateRenderer();
    }
}
