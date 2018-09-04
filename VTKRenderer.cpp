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
}

VTKRenderer::~VTKRenderer()
{
    delete ui;
}

vtkSmartPointer<vtkRenderer> VTKRenderer::GetRenderer() const
{
    return renderer_;
}

void VTKRenderer::UpdateRenderer()
{
    renderer_->ResetCamera();
    renderer_->Render();
    widget_->update();
}
