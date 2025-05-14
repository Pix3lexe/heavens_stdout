cmake_minimum_required(VERSION 3.16)
project(heavens_stdout LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_subdirectory(src)

add_executable(heavens_stdout src/main.cpp)

target_link_libraries(heavens_stdout PUBLIC
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    generatorlib
)
