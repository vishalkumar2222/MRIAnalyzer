#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = 0);
    ~ColorDialog();

    QColor GetMinColor() const;
    void SetMinColor(const QColor &min_color);

    QColor GetMaxColor() const;
    void SetMaxColor(const QColor &max_color);

private slots:
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

private:
    Ui::ColorDialog *ui;

    QColor min_color_;
    QColor max_color_;
};

#endif // COLORDIALOG_H
