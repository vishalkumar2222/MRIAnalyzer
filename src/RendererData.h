#ifndef RENDERERDATA_H
#define RENDERERDATA_H

#include <QObject>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <QVector3D>
#include <QMultiHash>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
class RendererData : public QObject
{
    Q_OBJECT
public:
    explicit RendererData(QObject *parent = 0);

    static RendererData *Get();

    vtkSmartPointer<vtkPolyData> GetMeshData() const;
    void SetMeshData(const vtkSmartPointer<vtkPolyData> &mesh_data);

    vtkSmartPointer<vtkImageData> GetImageData() const;
    void SetImageData(const vtkSmartPointer<vtkImageData> &image_data);

    QMultiHash<float, QVector3D> GetActivationPointHash() const;
    void SetActivationPointHash(const QMultiHash<float, QVector3D> &activation_point_hash);

    QList<float> GetActivationTime() const;
    void SetActivationTime(const QList<float> &activation_time);

    vtkSmartPointer<vtkPolyData> GetActivationData() const;

    void SetActivationData(const vtkSmartPointer<vtkPolyData> &activation_data);

signals:

public slots:

private:

    vtkSmartPointer<vtkPolyData> mesh_data_;
    vtkSmartPointer<vtkPolyData> activation_data_;
    vtkSmartPointer<vtkImageData> image_data_;
    QMultiHash<float, QVector3D> activation_point_hash_;
    QList<float> activation_time_;
};

#endif // RENDERERDATA_H
