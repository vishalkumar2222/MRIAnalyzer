#include "MRIMainWindow.h"
#include <QApplication>
#include <vtkAutoInit.h>
//Main
int main(int argc, char *argv[])
{
    VTK_MODULE_INIT(vtkRenderingOpenGL2);
    VTK_MODULE_INIT(vtkInteractionStyle);
    VTK_MODULE_INIT(vtkRenderingFreeType);
    VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
    QApplication a(argc, argv);
    MRIMainWindow w;
    w.showMaximized();

    return a.exec();
}
