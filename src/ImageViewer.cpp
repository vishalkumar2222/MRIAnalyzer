#include "ImageViewer.h"
#include "ui_ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider_level,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->horizontalSlider_window,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->spinBox_level,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->spinBox_window,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->comboBox_orientation,SIGNAL(currentIndexChanged(int)),SLOT(ValueChanged()));
    connect(ui->horizontalSlider_slices,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->spinBox_slices,SIGNAL(valueChanged(int)),SLOT(ValueChanged()));
    connect(ui->pushButton_reset_camera,SIGNAL(clicked(bool)),this,SLOT(ValueChanged()));
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::SetInfo()
{
    ui->horizontalSlider_window->setValue(info_.window);
    ui->horizontalSlider_level->setValue(info_.level);
    if(info_.plane == orientation::kXY)
    {
        ui->comboBox_orientation->setCurrentText("XY");
    }
    else if(info_.plane == orientation::kYZ)
    {
        ui->comboBox_orientation->setCurrentText("YZ");
    }
    else if(info_.plane == orientation::kXZ)
    {
        ui->comboBox_orientation->setCurrentText("XZ");
    }

    ui->spinBox_slices->setRange(info_.min_slice_, info_.max_slice_);
    ui->horizontalSlider_slices->setRange(info_.min_slice_, info_.max_slice_);

    ui->horizontalSlider_slices->setValue(info_.current_slice_);
}

ImageViewer::SettingInfo &ImageViewer::GetInfo()
{
    return info_;
}

void ImageViewer::ValueChanged()
{
    info_.level = ui->spinBox_level->value();
    info_.window = ui->spinBox_window->value();
    if(ui->comboBox_orientation->currentText() == "XY")
    {
        info_.plane = orientation::kXY;
    }
    else if(ui->comboBox_orientation->currentText() == "YZ")
    {
        info_.plane = orientation::kYZ;
    }
    else if(ui->comboBox_orientation->currentText() == "XZ")
    {
        info_.plane = orientation::kXZ;
    }

    info_.current_slice_ = ui->horizontalSlider_slices->value();

    emit ApplyClicked();
}
