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
#include <QMessageBox>
#include <QMenu>

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

    void on_action_Set_Background_Color_triggered();

    void on_action_Show_Scar_triggered();

    void on_action_Show_Activation_Time_triggered();

    void on_action_Color_Map_Editor_triggered();


    void on_treeView_customContextMenuRequested(const QPoint &pos);

private:

    void ReadImageData(const QString& filename);
    void ReadMeshData(const QString& filename);

    void SplitMeshFile(const vtkSmartPointer<vtkPolyData> &source);

    Ui::MRIMainWindow *ui;
    AnimationWidget *animate_widget_;
    ProjectTreeModel *project_model_;
    TreeItem *root_item_;
    TreeItem *image_Stack_item_;
    TreeItem *mesh_item_;
    TreeItem *activation_time_;
    RendererTabWidget *tab_widget_;
    QMenu *context_menu_;

};

#endif // MRIMAINWINDOW_H
