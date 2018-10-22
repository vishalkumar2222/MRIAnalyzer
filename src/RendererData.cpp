#include "RendererData.h"

RendererData::RendererData(QObject *parent) : QObject(parent)
{

}

RendererData *RendererData::Get()
{
    static RendererData renderer_data;

    return &renderer_data;
}

QMultiHash<float, QVector3D> RendererData::GetActivationPointHash() const
{
    return activation_point_hash_;
}

void RendererData::SetActivationPointHash(const QMultiHash<float, QVector3D> &activation_point_hash)
{
    activation_point_hash_ = activation_point_hash;
}

QList<float> RendererData::GetActivationTime() const
{
    return activation_time_;
}

void RendererData::SetActivationTime(const QList<float> &activation_time)
{
    activation_time_ = activation_time;
}

vtkSmartPointer<vtkPolyData> RendererData::GetActivationData() const
{
    return activation_data_;
}

void RendererData::SetActivationData(const vtkSmartPointer<vtkPolyData> &activation_data)
{
    activation_data_ = vtkSmartPointer<vtkPolyData>::New();
    activation_data_->DeepCopy(activation_data);
}

vtkSmartPointer<vtkPolyData> RendererData::GetMeshData() const
{
    return mesh_data_;
}

void RendererData::SetMeshData(const vtkSmartPointer<vtkPolyData> &mesh_data)
{    
    vtkSmartPointer<vtkDoubleArray> scar = vtkSmartPointer<vtkDoubleArray>::New();
    scar->SetName("scar");
    while(mesh_data->GetPointData()->GetNumberOfArrays() != 0)
    {
        if(QString(mesh_data->GetPointData()->GetArrayName(0)) == "scar")
        {
            scar->DeepCopy(mesh_data->GetPointData()->GetArray(0));
        }
        mesh_data->GetPointData()->RemoveArray(0);
    }

    while(mesh_data->GetCellData()->GetNumberOfArrays() != 0)
    {
        mesh_data->GetCellData()->RemoveArray(0);
    }

    mesh_data_ = vtkSmartPointer<vtkPolyData>::New();
    mesh_data_->DeepCopy(mesh_data);
    mesh_data_->GetPointData()->SetScalars(scar);
}

vtkSmartPointer<vtkImageData> RendererData::GetImageData() const
{
    return image_data_;
}

void RendererData::SetImageData(const vtkSmartPointer<vtkImageData> &image_data)
{
    image_data_ = vtkSmartPointer<vtkImageData>::New();
    image_data_->DeepCopy(image_data);
}
