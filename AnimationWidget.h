#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AnimationWidget;
}

class AnimationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationWidget(QWidget *parent = 0);
    ~AnimationWidget();

    static AnimationWidget *GetWidget();

    void AnimationStatus(bool status);

signals:
    void PlayButtonClicked();

    void RecordButtonClicked();

    void StopButtonClicked();


private:
    Ui::AnimationWidget *ui;
};

#endif // ANIMATIONWIDGET_H
