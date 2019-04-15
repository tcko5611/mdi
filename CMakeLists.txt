cmake_minimum_required(VERSION 3.2)
project(mdi)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(mdi mainwindow.ui MdiMainWindow.ui mdi.qrc mainwindow.h MdiChild.h MdiMainWindow.h mainwindow.cpp MdiChild.cpp MdiMainWindow.cpp main.cpp)

qt5_use_modules(mdi Core Widgets)
