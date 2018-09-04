#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include "ComboBoxDelegate.h"
#include "FileExplorer.h"

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = 0);
    ~ImportDialog();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::ImportDialog *ui;
    FileExplorer *explorer_;
};

#endif // IMPORTDIALOG_H
