#ifndef MRIMAINWINDOW_H
#define MRIMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "VTKRenderer.h"
#include "ImportDialog.h"
#include "AnimationWidget.h"
#include "ParticleMapper.h"
#include "ProjectTreeModel.h"
#include <algorithm>
#include "RendererTabWidget.h"
#include "RendererData.h"
#include <QSettings>

namespace Ui {
class MRIMainWindow;
}

class MRIMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MRIMainWindow(QWidget *parent = 0);
    ~MRIMainWindow();

private slots:

    void on_action_Import_Data_triggered();

    void on_action_Slice_View_triggered();

    void on_action_3D_View_triggered();

    void on_action_Set_Background_Color_triggered();

    void on_action_Show_Scar_triggered(bool checked);

    void on_action_Change_Color_Min_Max_triggered();

private:

    void ReadImageData(const QString& filename);
    void ReadMeshData(const QString& filename);

    void CalculateAndSetDistanceToCell(vtkSmartPointer<vtkPolyData>& input);

    void SplitMeshFile(const vtkSmartPointer<vtkPolyData> &source);

    Ui::MRIMainWindow *ui;
    AnimationWidget *animate_widget_;
    ProjectTreeModel *project_model_;
    TreeItem *root_item_;
    TreeItem *image_Stack_item_;
    TreeItem *mesh_item_;
    TreeItem *activation_time_;
    RendererTabWidget *tab_widget_;

};

#endif // MRIMAINWINDOW_H
