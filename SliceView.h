#ifndef SLICEVIEW_H
#define SLICEVIEW_H

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

namespace Ui {
class SliceView;
}

class SliceView : public QWidget
{
    Q_OBJECT

public:
    explicit SliceView(const QString &name, QWidget *parent = 0);
    ~SliceView();

    void SetNumberOfSlices(int number);

    void SetCurrentSlice(int num);

    vtkSmartPointer<vtkRenderer> GetRenderer() const;

    void UpdateRenderer();
private:
    Ui::SliceView *ui;
    QVTKOpenGLWidget *widget_;
    vtkSmartPointer<vtkRenderer> renderer_;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> render_window_;
};

#endif // SLICEVIEW_H
