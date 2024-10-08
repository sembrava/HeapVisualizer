cmake_minimum_required(VERSION 3.16)

project(HeapVisualizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appHeapVisualizer

)

qt_add_qml_module(appHeapVisualizer
    URI HeapVisualizer
    VERSION 1.0
    QML_FILES

        QML_FILES src/view/ui/Main.qml
        SOURCES src/main.cpp
        SOURCES src/persistence/filemanager.h
        SOURCES
        SOURCES src/persistence/csvfilemanager.h src/persistence/csvfilemanager.cpp
        SOURCES src/utils/utils.h
        SOURCES src/utils/utils.cpp
        SOURCES
        SOURCES src/model/snapshots/heapsortsnapshot.h
        SOURCES src/model/snapshots/removemaxsnapshot.h
        SOURCES src/model/snapshots/addnodesnapshot.h
        SOURCES src/model/heapalgorithms.h
        SOURCES src/model/heapalgorithms.cpp
        SOURCES src/model/visualizers/heapalgorithmvisualizer.h
        SOURCES src/model/visualizers/heapsortvisualizer.h src/model/visualizers/heapsortvisualizer.cpp
        QML_FILES src/view/ui/pages/HomePage.qml
        QML_FILES src/view/ui/pages/EditorPage.qml
        QML_FILES src/view/ui/pages/VisualizerPage.qml
        SOURCES src/view/modelmanager.h src/view/modelmanager.cpp
        SOURCES src/view/models/homemodel.h src/view/models/homemodel.cpp
        SOURCES src/view/models/editormodel.h src/view/models/editormodel.cpp
        SOURCES src/view/models/visualizermodel.h src/view/models/visualizermodel.cpp
        QML_FILES src/view/ui/general/HoverButton.qml
        SOURCES src/view/models/completebinarytree.h
        SOURCES src/persistence/treefileinfo.h
        SOURCES src/globals.h
        QML_FILES
        QML_FILES src/view/ui/logic/PositionCalculator.js
        QML_FILES
        QML_FILES
        QML_FILES src/view/ui/logic/Animations.js
        QML_FILES
        SOURCES
        SOURCES src/view/ui/qmlglobals.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHeapVisualizer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHeapVisualizer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHeapVisualizer
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appHeapVisualizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
