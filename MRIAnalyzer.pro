#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T19:33:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MRIAnalyzer
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    MRIMainWindow.cpp \
    SliceView.cpp \
    VTKRenderer.cpp \
    ImportDialog.cpp

 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkalglib-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkChartsCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonColor-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonComputationalGeometry-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonDataModel-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonExecutionModel-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonMath-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonMisc-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonSystem-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkCommonTransforms-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkDICOMParser-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkDomainsChemistry-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkDomainsChemistryOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkexoIIc-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkexpat-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersAMR-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersExtraction-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersFlowPaths-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersGeneral-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersGeneric-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersGeometry-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersHybrid-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersHyperTree-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersImaging-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersModeling-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersParallel-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersParallelImaging-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersPoints-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersProgrammable-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersSelection-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersSMP-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersSources-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersStatistics-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersTexture-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersTopology-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkFiltersVerdict-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkfreetype-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkGeovisCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkgl2ps-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkglew-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkGUISupportQt-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkGUISupportQtSQL-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkhdf5-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkhdf5_hl-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingColor-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingFourier-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingGeneral-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingHybrid-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingMath-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingMorphological-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingSources-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingStatistics-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkImagingStencil-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkInfovisCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkInfovisLayout-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkInteractionImage-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkInteractionStyle-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkInteractionWidgets-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOAMR-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOEnSight-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOExodus-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOExport-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOExportOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOGeometry-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOImage-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOImport-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOInfovis-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOLegacy-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOLSDyna-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOMINC-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOMovie-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIONetCDF-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOParallel-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOParallelXML-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOPLY-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOSQL-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOTecplotTable-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOVideo-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOXML-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkIOXMLParser-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkjpeg-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkjsoncpp-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtklibharu-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtklibxml2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtklz4-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkmetaio-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkNetCDF-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtknetcdfcpp-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkoggtheora-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkParallelCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkpng-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkproj4-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingAnnotation-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingContext2D-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingContextOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingFreeType-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingGL2PSOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingImage-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingLabel-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingLOD-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingQt-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingVolume-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkRenderingVolumeOpenGL2-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtksqlite-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtksys-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtktiff-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkverdict-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkViewsContext2D-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkViewsCore-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkViewsInfovis-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkViewsQt-8.1
 LIBS += -L$$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/lib/ -lvtkzlib-8.1

INCLUDEPATH += $$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/include/vtk-8.1
DEPENDPATH += $$PWD/../../DevelopmentCode/ThirdPartyLibraries/VTK-8.1.0_INSTALL/include/vtk-8.1



FORMS += MRIMainWindow.ui \
    SliceView.ui \
    VTKRenderer.ui \
    ImportDialog.ui


HEADERS += \
    MRIMainWindow.h \
    SliceView.h \
    VTKRenderer.h \
    ImportDialog.h \
    SliceInteratorStyle.h
