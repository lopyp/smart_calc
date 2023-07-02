cmake_minimum_required(VERSION 3.5)

project(smart_calc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport)
find_library(
            calc_lib
            NAMES libs21_calc s21_calc 
            HINTS "${CMAKE_SOURCE_DIR}"
            #HINTS "/Users/donnette/project/calc/src/calc/"
            #NO_DEFAULT_PATH
)
#message(STATUS "DIRS =: ${CMAKE_SOURCE_DIR}")
#message(STATUS "LIB_LOCATION : ${calc_lib}")
#message(STATUS "${PROJECT_SOURCES_DIR}")


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qcustomplot.cpp
        qcustomplot.h
        credit.h
        credit.cpp
        credit.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smart_calc
        #PrintSupport
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET smart_calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(smart_calc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smart_calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(smart_calc PRIVATE ${calc_lib})

set_target_properties(smart_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smart_calc)
endif()
