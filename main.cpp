#include "MRIMainWindow.h"
#include <QApplication>
#include <vtkAutoInit.h>

int main(int argc, char *argv[])
{
    VTK_MODULE_INIT(vtkRenderingOpenGL2);
    VTK_MODULE_INIT(vtkInteractionStyle);
    VTK_MODULE_INIT(vtkRenderingFreeType);
    QApplication a(argc, argv);
    MRIMainWindow w;
    w.showMaximized();

    return a.exec();
}
