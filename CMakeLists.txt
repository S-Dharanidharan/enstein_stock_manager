cmake_minimum_required(VERSION 3.16)

project(EnsteinStockManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Gui Qml)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/QXlsx/QXlsx/CMakeLists.txt")
    add_subdirectory(QXlsx/QXlsx)
    message(STATUS "QXlsx found and added")
else()
    message(FATAL_ERROR "QXlsx not found!")
endif()

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(EnsteinStockManager
    main.cpp
)

qt_add_qml_module(EnsteinStockManager
    URI Enstein
    QML_FILES
        Main.qml
        SOURCES excelhandler.h
        SOURCES excelhandler.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(EnsteinStockManager PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEnstein
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(EnsteinStockManager
    PRIVATE Qt6::Quick
            Qt6::Core
            Qt6::Gui
            Qt6::Qml
            QXlsx::QXlsx
)

include(GNUInstallDirs)
install(TARGETS EnsteinStockManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
