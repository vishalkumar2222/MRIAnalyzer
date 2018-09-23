#include "ImportDialog.h"
#include "ui_ImportDialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    model_ = new QStringListModel();
    ui->listView_files->setModel(model_);
    //files_<<"/home/ess/Downloads/pig21_bssfp_cropped.nii" << "/home/ess/Downloads/VT15_actTimes.vtk" <<"/home/ess/Downloads/pig21_imaging.vtk";
    files_<<"/home/ess/Downloads/pig21_bssfp_cropped.nii" << "/home/ess/Downloads/VT15_actTimes.vtk";
    model_->setStringList(files_);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::on_pushButton_add_clicked()
{

    QStringList files = QFileDialog::getOpenFileNames(this,tr("Add"),tr("Files(*.vtk *.nii"));

    for(const auto& file : files)
    {
        files_.append(file);
    }
    model_->setStringList(files_);
}

void ImportDialog::on_pushButton_remove_clicked()
{
    if(ui->listView_files->currentIndex().isValid())
    {
        int row = ui->listView_files->currentIndex().row();
        files_.removeAt(row);
        model_->setStringList(files_);
    }
}

void ImportDialog::on_listView_files_clicked(const QModelIndex &index)
{
    if(index.isValid())
        ui->pushButton_remove->setEnabled(true);
}

QStringList ImportDialog::GetFiles() const
{
    return files_;
}
