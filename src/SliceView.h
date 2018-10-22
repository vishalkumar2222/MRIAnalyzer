#ifndef SLICEVIEW_H
#define SLICEVIEW_H

#include <QSplitter>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include "SliceInteratorStyle.h"
#include "ImageViewer.h"

class SliceInteratorStyle;

class SliceView : public QSplitter
{
    Q_OBJECT

public:
    explicit SliceView(QWidget *parent = 0);
    ~SliceView();

    void UpdateRenderer();

    vtkSmartPointer<vtkImageViewer2> GetImageViewer() const;

    void UpdateImageViewerInfo();

    ImageViewer::SettingInfo &GetSettingsInfo();

    void CurrentSliceChanged(int slice);

private slots:

    void ApplyClicked();

private:
    QVTKOpenGLWidget *widget_;
    ImageViewer *image_controller_;
    SliceInteratorStyle *image_interactor_style_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
    vtkSmartPointer<vtkImageViewer2> image_viewer_;
};

#endif // SLICEVIEW_H
