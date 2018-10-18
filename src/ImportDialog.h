#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QFileDialog>
namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = 0);
    ~ImportDialog();

    const QString GetImageFileName();
    const QString GetMeshFileName();
    const QString GetActivationTime();

private slots:

    void on_pushButton_browse_image_clicked();

    void on_pushButton_browse_mesh_clicked();

    void on_pushButton_browse_active_clicked();

private:
    Ui::ImportDialog *ui;
};

#endif // IMPORTDIALOG_H
