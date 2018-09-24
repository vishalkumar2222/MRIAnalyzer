#include "SliceView.h"
#include "ui_SliceView.h"

SliceView::SliceView(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliceView)
{
    ui->setupUi(this);

    ui->label_view_name->setText(name);

    image_viewer_ = vtkSmartPointer<vtkImageViewer2>::New();

   // renderer_ = vtkSmartPointer<vtkRenderer>::New();
    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    image_viewer_->SetRenderWindow(render_window_.Get());
  //  render_window_->AddRenderer(renderer_.Get());
    widget_ = new QVTKOpenGLWidget(this);
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    //renderer_->SetBackground(0.5,0.5,0.5);
    image_interactor_style_ = new SliceInteratorStyle;
    render_window_->GetInteractor()->SetInteractorStyle(image_interactor_style_);
   // image_interactor_style_->SetInteractionModeToImageSlicing();
    ui->verticalLayout->addWidget(widget_, 1);
}

SliceView::~SliceView()
{
    delete ui;
    if(image_interactor_style_ !=nullptr)
    {
        image_interactor_style_->Delete();
    }
}

void SliceView::SetNumberOfSlices(int number)
{
    ui->horizontalSlider->setMaximum(number);
    ui->spinBox->setMaximum(number);
}

void SliceView::SetCurrentSlice(int num)
{
    ui->horizontalSlider->setValue(num);
    ui->spinBox->setValue(num);
}

vtkSmartPointer<vtkRenderer> SliceView::GetRenderer() const
{
    return renderer_;
}

void SliceView::UpdateRenderer()
{
    //renderer_->ResetCamera();
    //renderer_->Render();
    image_interactor_style_->SetImageViewer(image_viewer_.Get());
    SetNumberOfSlices(image_viewer_->GetSliceMax());
    image_viewer_->Render();
    widget_->update();
    this->update();
}

vtkSmartPointer<vtkImageViewer2> SliceView::GetImageViewer() const
{
    return image_viewer_;
}
