#include "SliceView.h"
#include "ui_SliceView.h"

SliceView::SliceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliceView)
{
    ui->setupUi(this);

    image_viewer_ = vtkSmartPointer<vtkImageViewer2>::New();

    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    image_viewer_->SetRenderWindow(render_window_.Get());
    widget_ = new QVTKOpenGLWidget(this);
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    image_interactor_style_ = new SliceInteratorStyle;
    render_window_->GetInteractor()->SetInteractorStyle(image_interactor_style_);
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

void SliceView::UpdateRenderer()
{
    image_viewer_->Render();
    widget_->update();
    this->update();
}

vtkSmartPointer<vtkImageViewer2> SliceView::GetImageViewer() const
{
    return image_viewer_;
}

void SliceView::UpdateImageViewerInfo()
{
    image_interactor_style_->SetImageViewer(image_viewer_);
}
