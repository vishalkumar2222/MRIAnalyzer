#include "AppManager.h"

AppManager::AppManager()
{

}

AppManager *AppManager::Get()
{
    static AppManager manager;

    return &manager;
}

QSettings *AppManager::GetSettings()
{
    static QSettings setting("Contravolts","MRIAnalyzer");

    return &setting;
}
