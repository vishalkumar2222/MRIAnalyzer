#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT

public:

    enum orientation{kXY = 0, kYZ, kXZ};

    struct SettingInfo{
        int window;
        int level;
        orientation plane;
        int min_slice_;
        int max_slice_;
        int current_slice_;
    };

    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    void SetInfo();
    SettingInfo& GetInfo();

signals:
    void ApplyClicked();
private slots:
    void ValueChanged();

private:
    Ui::ImageViewer *ui;
    SettingInfo info_;
};

#endif // IMAGEVIEWER_H
