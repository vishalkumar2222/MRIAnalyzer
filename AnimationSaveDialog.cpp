#include "AnimationSaveDialog.h"
#include "ui_AnimationSaveDialog.h"

AnimationSaveDialog::AnimationSaveDialog(const QString &path, const QStringList &arguments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationSaveDialog)
{
    ui->setupUi(this);
    process_ = new QProcess(this);
    process_->setWorkingDirectory(path);
    connect(process_,SIGNAL(readyReadStandardOutput()),this,SLOT(ReadyRead()));
    connect(process_,SIGNAL(finished(int)),this,SLOT(Finished(int)));
    process_->start("ffmpeg", arguments);
    ui->textEdit_log->append(path);
    ui->textEdit_log->append("Saving.....");
}

AnimationSaveDialog::~AnimationSaveDialog()
{
    delete ui;
}

void AnimationSaveDialog::on_pushButton_ok_clicked()
{
    this->accept();
}

void AnimationSaveDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}

void AnimationSaveDialog::ReadyRead()
{
    QByteArray array = process_->readAllStandardOutput();
    ui->textEdit_log->append(QString::fromLatin1(array));
}

void AnimationSaveDialog::Finished(int exist_code)
{
    if(exist_code == QProcess::NormalExit)
    {
        ui->textEdit_log->append("Saved");
        ui->pushButton_ok->setEnabled(true);
    }
    else
    {
        ui->textEdit_log->append("Failed to save");
        ui->pushButton_ok->setEnabled(false);
    }
}
