#include "SliceView.h"
#include <vtkImageMapToWindowLevelColors.h>

SliceView::SliceView(QWidget *parent) :
    QSplitter(parent)
{
    image_controller_ = new ImageViewer();

    image_viewer_ = vtkSmartPointer<vtkImageViewer2>::New();

    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    image_viewer_->SetRenderWindow(render_window_.Get());
    widget_ = new QVTKOpenGLWidget();
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    image_interactor_style_ = new SliceInteratorStyle;
    render_window_->GetInteractor()->SetInteractorStyle(image_interactor_style_);
    addWidget(image_controller_);
    addWidget(widget_);
    connect(image_controller_,SIGNAL(ApplyClicked()),this,SLOT(ApplyClicked()));
}

SliceView::~SliceView()
{
    if(image_interactor_style_ !=nullptr)
    {
        image_interactor_style_->Delete();
    }
}

void SliceView::UpdateRenderer()
{
    render_window_->Render();
    image_controller_->SetInfo();
    this->update();
}

vtkSmartPointer<vtkImageViewer2> SliceView::GetImageViewer() const
{
    return image_viewer_;
}

void SliceView::UpdateImageViewerInfo()
{
    image_interactor_style_->SetImageViewer(image_viewer_, this);
}

ImageViewer::SettingInfo &SliceView::GetSettingsInfo()
{
    return image_controller_->GetInfo();
}

void SliceView::CurrentSliceChanged(int slice)
{
   image_controller_->GetInfo().current_slice_ = slice;

   image_controller_->SetInfo();
}

void SliceView::ApplyClicked()
{
    image_viewer_->SetColorLevel(image_controller_->GetInfo().level);
    image_viewer_->SetColorWindow(image_controller_->GetInfo().window);

    if(image_controller_->GetInfo().plane == ImageViewer::orientation::kXY)
    {
        image_viewer_->SetSliceOrientationToXY();
    }
    else if(image_controller_->GetInfo().plane == ImageViewer:: orientation::kYZ)
    {
        image_viewer_->SetSliceOrientationToYZ();
    }
    else if(image_controller_->GetInfo().plane == ImageViewer::orientation::kXZ)
    {
        image_viewer_->SetSliceOrientationToXZ();
    }

    image_interactor_style_->SetCurrentSlice(image_controller_->GetInfo().current_slice_);

    image_viewer_->Render();
}
