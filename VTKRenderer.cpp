#include "VTKRenderer.h"
#include "ui_VTKRenderer.h"

VTKRenderer::VTKRenderer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VTKRenderer)
{
    ui->setupUi(this);

    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    render_window_->AddRenderer(renderer_.Get());
    widget_ = new QVTKOpenGLWidget(this);
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    renderer_->SetBackground(0.5,0.5,0.5);
    ui->verticalLayout->addWidget(widget_, 1);
    image_style_interactor_ = vtkSmartPointer<vtkInteractorStyleImage>::New();
    track_ball_interactor_style_ = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    render_window_->GetInteractor()->SetInteractorStyle(track_ball_interactor_style_);

}

VTKRenderer::~VTKRenderer()
{
    delete ui;
}

vtkSmartPointer<vtkRenderer> VTKRenderer::GetRenderer() const
{
    return renderer_;
}

void VTKRenderer::ChangeModeTo3D()
{
    render_window_->GetInteractor()->SetInteractorStyle(track_ball_interactor_style_);
}

void VTKRenderer::ChangeModeTo2DImage()
{
    render_window_->GetInteractor()->SetInteractorStyle(image_style_interactor_);
}

void VTKRenderer::UpdateRenderer()
{
    renderer_->ResetCamera();
    renderer_->Render();
    this->update();
}

void VTKRenderer::UpdateRendererWidget()
{
    renderer_->Render();
    this->update();
}


void VTKRenderer::ChangeCameraToTopView()
{
    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(0,0,-1);
    renderer_->GetActiveCamera()->SetViewUp(0,1,0);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ChangeCameraToBottomView()
{

    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(0,0,1);
    renderer_->GetActiveCamera()->SetViewUp(0,1,0);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ChangeCameraToLeftView()
{

    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(1,0,0);
    renderer_->GetActiveCamera()->SetViewUp(0,0,1);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ChangeCameraToRightView()
{
    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(-1,0,0);
    renderer_->GetActiveCamera()->SetViewUp(0,0,1);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ChangeCameraToFrontView()
{
    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(0,1,0);
    renderer_->GetActiveCamera()->SetViewUp(0,0,1);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ChangeCameraToBackView()
{
    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(0,-1,0);
    renderer_->GetActiveCamera()->SetViewUp(0,0,1);
    renderer_->ResetCamera();
    this->update();
}

void VTKRenderer::ResetCamera()
{
    renderer_->GetActiveCamera()->SetViewUp(0,0,1);
    renderer_->GetActiveCamera()->SetPosition(0,0,0);
    renderer_->GetActiveCamera()->SetFocalPoint(-1,1,0);
    renderer_->ResetCamera();
    this->update();
}
