cmake_minimum_required(VERSION 3.1)

project(MRIAnalyzer
   LANGUAGES CXX
   VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_STANDARD 11)


file(GLOB UI_FILES src/*.ui)
file(GLOB QT_WRAP src/*.h)
file(GLOB CXX_FILES src/*.cpp)
file(GLOB RC_FILES src/*.qrc)


find_package(VTK REQUIRED PATHS ${CMAKE_CURRENT_BINARY_DIR}/../../../DevelopmentCode/ThirdPartyLibraries/VTK-Build NO_DEFAULT_PATH)
include(${VTK_USE_FILE})
message("VTK Path:${VTK_DIR_PATH}")

if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
   qt5_wrap_cpp(QtSources ${QT_WRAP} )
   qt5_wrap_ui(UISrcs ${UI_FILES} )
   qt5_add_resources(RCSrcs ${RC_FILES})
   #CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(MRIAnalyzer WIN32
    ${CXX_FILES} ${UISrcs} ${QtSources} ${RCSrcs})
  qt5_use_modules(MRIAnalyzer Core Gui Widgets)
  target_link_libraries(MRIAnalyzer ${VTK_LIBRARIES})
else()
message("Please user VTK version greater thah 6 with Qt and FFMPEG enabled")
endif()
