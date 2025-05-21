cmake_minimum_required(VERSION 3.16)
project(heavens_stdout LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()
qt_add_resources(RESOURCE_GEN resources/resources.qrc)

qt_add_executable(heavens_stdout
    src/main.cpp
    ${RESOURCE_GEN}
)

add_subdirectory(src)
