#include "SliceView.h"
#include "ui_SliceView.h"

SliceView::SliceView(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliceView)
{
    ui->setupUi(this);

    ui->label_view_name->setText(name);

    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    render_window_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    render_window_->AddRenderer(renderer_.Get());
    widget_ = new QVTKOpenGLWidget(this);
    widget_->SetRenderWindow(render_window_.Get());
    render_window_->SetMultiSamples(0);
    renderer_->SetBackground(0.0,0.0,0.0);
    ui->verticalLayout->addWidget(widget_, 1);
}

SliceView::~SliceView()
{
    delete ui;
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
    renderer_->ResetCamera();
    renderer_->Render();
    widget_->update();
    this->update();
}
