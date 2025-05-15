target_sources(heavens_stdout PRIVATE
    heavensstdout.h
    heavensstdout.cpp
    heavensstdout.ui
)

target_include_directories(heavens_stdout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
