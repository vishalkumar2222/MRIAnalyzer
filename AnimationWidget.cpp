#include "AnimationWidget.h"
#include "ui_AnimationWidget.h"

AnimationWidget::AnimationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton_play_pause,SIGNAL(clicked(bool)),this,SIGNAL(PlayButtonClicked()));
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
    ui->pushButton_play_pause->setEnabled(!status);
}
