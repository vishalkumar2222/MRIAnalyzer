#include "MRIMainWindow.h"
#include "ui_MRIMainWindow.h"
#include "TreeItem.h"
#include "AppManager.h"
#include <vtkCellData.h>

MRIMainWindow::MRIMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MRIMainWindow)
{
    ui->setupUi(this);

    animate_widget_ = new AnimationWidget(this);

    RendererData::Get();

    QString style="QTreeView::branch:has-siblings:!adjoins-item {"
                  "border-image: url(:/images/vline.png) 0;"
                  "}"

                  "QTreeView::branch:has-siblings:adjoins-item {"
                  "border-image: url(:/images/branch-more.png) 0;"
                  "}"

                  "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
                  "border-image: url(:/images/branch-end.png) 0;"
                  " }"

                  "QTreeView::branch:has-children:!has-siblings:closed,"
                  " QTreeView::branch:closed:has-children:has-siblings {"
                  "border-image: none;"
                  "image: url(:/images/plus.png);"
                  "}"

                  "QTreeView::branch:open:has-children:!has-siblings,"
                  " QTreeView::branch:open:has-children:has-siblings  {"
                  "border-image: none;"
                  "image: url(:/images/minus.png);"
                  "}";
    ui->treeView->setStyleSheet(style);


    root_item_ = new TreeItem("Workspace");

    image_Stack_item_ = new TreeItem("Image Stack", root_item_);
    root_item_->appendChild(image_Stack_item_);


    mesh_item_ = new TreeItem("Mesh", root_item_);
    root_item_->appendChild(mesh_item_);

    activation_time_ = new TreeItem("Activation Time" , root_item_);
    root_item_->appendChild(activation_time_);


    project_model_ = new ProjectTreeModel(this);
    project_model_->SetRootEntity(root_item_);
    ui->treeView->setModel(project_model_);
    ui->treeView->expandAll();


    tab_widget_ = new RendererTabWidget();
    ui->verticalLayout_main->addWidget(tab_widget_);
    ui->verticalLayout_main->addWidget(animate_widget_);

    context_menu_ = new QMenu();
    context_menu_->addActions(QList<QAction*>()<<ui->action_Show_Scar<<ui->action_Show_Activation_Time);

    connect(animate_widget_,&AnimationWidget::StopButtonClicked, [this](){
        tab_widget_->StopButtonClicked();
        animate_widget_->AnimationStatus(false);
    });

    connect(animate_widget_,&AnimationWidget::RecordButtonClicked,[this](){
        tab_widget_->RecordButtonClicked();
    });

    connect(tab_widget_,&RendererTabWidget::WriteLogs,[this](QString log){
        ui->statusbar->showMessage(log);
    });

    connect(animate_widget_,&AnimationWidget::PlayButtonClicked,[this](){
        animate_widget_->AnimationStatus(true);
        tab_widget_->StartAnimation(animate_widget_->GetTimer());
    });

    connect(animate_widget_,&AnimationWidget::PauseButtonClicked,[this](){
        tab_widget_->PauseAnimation();
    });

    connect(project_model_,&ProjectTreeModel::VisibilityChanged,[this](const QString& name, bool visibility){
        tab_widget_->SetActorVisibility(name, visibility);
    });

}

MRIMainWindow::~MRIMainWindow()
{
    delete ui;
}

void MRIMainWindow::on_action_Import_Data_triggered()
{
    ImportDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        tab_widget_->ClearAllData();
        if(image_Stack_item_->childCount() != 0)
        {
            image_Stack_item_->removeAllChild();
        }
        if(mesh_item_->childCount() != 0)
        {
            mesh_item_->removeAllChild();
        }
        if(activation_time_->childCount() != 0)
        {
            activation_time_->removeAllChild();
        }
        ReadMeshData(dialog.GetMeshFileName());
        ReadMeshData(dialog.GetActivationTime());
        ReadImageData(dialog.GetImageFileName());
        AppManager::Get()->GetSettings()->setValue("image", dialog.GetImageFileName());
        AppManager::Get()->GetSettings()->setValue("mesh", dialog.GetMeshFileName());
        AppManager::Get()->GetSettings()->setValue("active", dialog.GetActivationTime());

        tab_widget_->ShowImageInterpolation();

        project_model_->SetRootEntity(root_item_);
        ui->treeView->expandAll();
        tab_widget_->UpdateRenderer();
    }
}

void MRIMainWindow::ReadImageData(const QString &filename)
{
    vtkSmartPointer<vtkNIFTIImageReader> reader =
            vtkSmartPointer<vtkNIFTIImageReader>::New();

    reader->SetFileName(filename.toStdString().c_str());
    reader->Update();

    if (reader->GetErrorCode() != vtkErrorCode::NoError)
    {
        QMessageBox::information(this,tr("Status"),tr("Unable to read the file."));
        return;
    }

    RendererData::Get()->SetImageData(reader->GetOutput());

    QFileInfo info(filename);
    TreeItem *item = new TreeItem(info.baseName(), image_Stack_item_, true);
    image_Stack_item_->appendChild(item);
    tab_widget_->AddImageStack(info.baseName());

}

void MRIMainWindow::ReadMeshData(const QString &filename)
{
    // Get all data from the file
    vtkSmartPointer<vtkGenericDataObjectReader> reader =
            vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(filename.toStdString().c_str());
    reader->Update();

    QFileInfo info(filename);

    // All of the standard data types can be checked and obtained like this:
    if(reader->IsFilePolyData())
    {
        if(reader->GetPolyDataOutput()->GetNumberOfVerts() > 0)
        {
            this->SplitMeshFile(reader->GetPolyDataOutput());

            RendererData::Get()->SetActivationData(reader->GetPolyDataOutput());

            TreeItem *item = new TreeItem(info.baseName(), activation_time_, false);
            activation_time_->appendChild(item);
            return;
        }
        else
        {
            RendererData::Get()->SetMeshData(reader->GetPolyDataOutput());
            TreeItem *item = new TreeItem(info.baseName(), mesh_item_, true);
            mesh_item_->appendChild(item);
            tab_widget_->AddMesh(info.baseName());
        }

    }
    else
    {
        QMessageBox::information(this,tr("Status"),tr("Data not found!"));
    }
}

void MRIMainWindow::SplitMeshFile(const vtkSmartPointer<vtkPolyData>& source)
{

    vtkDataArray *scalers = source->GetCellData()->GetScalars();

    QMultiHash<float, QVector3D> hash;

    for(vtkIdType id = 0; id<source->GetNumberOfCells(); id++)
    {
        vtkCell *cell = source->GetCell(id);
        vtkPoints *points = cell->GetPoints();

        if(cell->GetCellType() == VTK_VERTEX)
        {
            double point[3] = {0.0,0.0,0.0};
            points->GetPoint(0,point);

            hash.insert(scalers->GetTuple1(id), QVector3D(point[0],point[1],point[2]));
        }
    }

    auto activation_time = hash.uniqueKeys();

    std::sort(activation_time.begin(), activation_time.end());

    RendererData::Get()->SetActivationTime(activation_time);

    RendererData::Get()->SetActivationPointHash(hash);
}

void MRIMainWindow::on_action_Set_Background_Color_triggered()
{
    tab_widget_->SetBackgroundColorTriggered();
}

void MRIMainWindow::on_action_Show_Scar_triggered()
{
    tab_widget_->ShowScar();
}

void MRIMainWindow::on_action_Show_Activation_Time_triggered()
{
    tab_widget_->ShowInterpolatedActivationTime();
}

void MRIMainWindow::on_action_Color_Map_Editor_triggered()
{
    tab_widget_->ChangeMinMaxColorActionTriggered();
}

void MRIMainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);

    if(index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

        if(item != nullptr)
        {
            if(item->IsMesh())

            {
                if(item->parentItem()->GetName()=="Mesh")
                {
                    context_menu_->exec(ui->treeView->mapToGlobal(pos));
                }
            }
        }
    }
}
