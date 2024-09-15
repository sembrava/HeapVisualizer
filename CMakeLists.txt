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
        SOURCES src/persistence/treefileinfo.h src/persistence/treefileinfo.cpp
        SOURCES src/persistence/csvfilemanager.h src/persistence/csvfilemanager.cpp
        SOURCES src/utils/utils.h
        SOURCES src/utils/utils.cpp
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
