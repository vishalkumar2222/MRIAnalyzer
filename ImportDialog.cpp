#include "ImportDialog.h"
#include "ui_ImportDialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

const QString ImportDialog::GetImageFileName()
{
    return ui->lineEdit_image->text();
}

const QString ImportDialog::GetMeshFileName()
{
    return ui->lineEdit_mesh->text();
}

const QString ImportDialog::GetActivationTime()
{
    return ui->lineEdit_active->text();
}

void ImportDialog::on_pushButton_browse_image_clicked()
{

    QString file = QFileDialog::getOpenFileName(this,tr("Add Image"),tr("Files(*.nii)"));

    ui->lineEdit_image->setText(file);
}

void ImportDialog::on_pushButton_browse_mesh_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Add Mesh"),tr("Files(*.vtk)"));

    ui->lineEdit_mesh->setText(file);
}

void ImportDialog::on_pushButton_browse_active_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Add Activation"),tr("Files(*.vtk)"));

    ui->lineEdit_active->setText(file);
}
