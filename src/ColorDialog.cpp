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

    SetMinColor(color);
}

void ColorDialog::on_pushButton_max_clicked()
{
    QColor color = QColorDialog::getColor(max_color_,this,tr("Choose Color"), QColorDialog::DontUseNativeDialog);

    SetMaxColor(color);
}

QColor ColorDialog::GetMaxColor() const
{
    return max_color_;
}

void ColorDialog::SetMaxColor(const QColor &max_color)
{
    max_color_ = max_color;
    QString color = QString::asprintf("background-color: rgba(%d, %d, %d, %d)",max_color_.red(),
                                      max_color_.green()
                                      ,max_color_.blue()
                                      ,max_color_.alpha());

    ui->pushButton_max->setStyleSheet(color);
}

QColor ColorDialog::GetMinColor() const
{
    return min_color_;
}

void ColorDialog::SetMinColor(const QColor &min_color)
{
    min_color_ = min_color;
    QString color = QString::asprintf("background-color: rgba(%d, %d, %d, %d)",min_color_.red(),
                                      min_color_.green()
                                      ,min_color_.blue()
                                      ,min_color_.alpha());

    ui->pushButton_min->setStyleSheet(color);
}
