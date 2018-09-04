#include "ImportDialog.h"
#include "ui_ImportDialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    ComboBoxDelegate *delegate = new ComboBoxDelegate();
    ui->tableView->setItemDelegate(delegate);
    explorer_ = new FileExplorer();
    ui->tableView->setModel(explorer_);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::on_pushButton_add_clicked()
{
    explorer_->AddFileName("/home/ess/Downloads/pig21_imaging.vtk");
}
