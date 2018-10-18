#include "ColorDialog.h"
#include "ui_ColorDialog.h"

ColorDialog::ColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
    min_color_ = QColor(Qt::blue);
    max_color_ = QColor(Qt::red);
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::on_pushButton_min_clicked()
{
    QColor color = QColorDialog::getColor(min_color_,this,tr("Choose Color"), QColorDialog::DontUseNativeDialog);

    min_color_ = color;


}

void ColorDialog::on_pushButton_max_clicked()
{
    QColor color = QColorDialog::getColor(max_color_,this,tr("Choose Color"), QColorDialog::DontUseNativeDialog);

    max_color_ = color;
}

QColor ColorDialog::GetMaxColor() const
{
    return max_color_;
}

void ColorDialog::SetMaxColor(const QColor &max_color)
{
    max_color_ = max_color;
    ui->pushButton_max->setStyleSheet(QString::asprintf("background-color: rgba(%d, %d, %d, %d)",max_color.red(),
                                                        max_color.green()
                                                        ,max_color.blue()
                                                        ,max_color.alpha()));
}

QColor ColorDialog::GetMinColor() const
{
    return min_color_;
}

void ColorDialog::SetMinColor(const QColor &min_color)
{
    min_color_ = min_color;
    ui->pushButton_max->setStyleSheet(QString::asprintf("background-color: rgba(%d, %d, %d, %d)",min_color.red(),
                                                        min_color.green()
                                                        ,min_color.blue()
                                                        ,min_color.alpha()));
}
