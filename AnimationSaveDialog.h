#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
namespace Ui {
class AnimationSaveDialog;
}

class AnimationSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationSaveDialog( const QString& path ,const QStringList& arguments, QWidget *parent = 0);
    ~AnimationSaveDialog();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void ReadyRead();

    void Finished(int exist_code);

private:
    QProcess *process_;
    Ui::AnimationSaveDialog *ui;

};

#endif // ANIMATIONDIALOG_H
