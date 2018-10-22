#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QSettings>

class AppManager
{
public:
    AppManager();

    static AppManager *Get();

    QSettings *GetSettings();
};

#endif // APPMANAGER_H
