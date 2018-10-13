#include "AnimationWidget.h"
#include "ui_AnimationWidget.h"

AnimationWidget::AnimationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton_play_pause,SIGNAL(clicked(bool)),this,SLOT(PlayPauseButtonClicked()));
    connect(ui->pushButton_record,SIGNAL(clicked(bool)),this,SIGNAL(RecordButtonClicked()));
    connect(ui->pushButton_stop,SIGNAL(clicked(bool)),this,SIGNAL(StopButtonClicked()));
}

AnimationWidget::~AnimationWidget()
{
    delete ui;
}

AnimationWidget *AnimationWidget::GetWidget()
{
    static AnimationWidget widget;

    return &widget;
}

void AnimationWidget::AnimationStatus(bool status)
{
    ui->pushButton_record->setEnabled(status);
    ui->pushButton_stop->setEnabled(status);
    if(!status)
    {
        ui->pushButton_play_pause->setText("Play");
    }
}

void AnimationWidget::PlayPauseButtonClicked()
{
    if(ui->pushButton_play_pause->text() == "Play")
    {
        emit PlayButtonClicked();
        ui->pushButton_play_pause->setText("Pause");
    }
    else if(ui->pushButton_play_pause->text() == "Pause")
    {
        emit PauseButtonClicked();
        ui->pushButton_play_pause->setText("Play");
    }
}
