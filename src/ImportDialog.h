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

    QStringList GetFiles() const;

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_remove_clicked();

    void on_listView_files_clicked(const QModelIndex &index);

private:
    Ui::ImportDialog *ui;
    QStringList files_;
    QStringListModel *model_;
};

#endif // IMPORTDIALOG_H
