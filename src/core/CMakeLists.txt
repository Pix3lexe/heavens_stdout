target_sources(heavens_stdout PRIVATE
    heavens_stdout.h
    heavens_stdout.cpp
    heavens_stdout.ui
)

target_include_directories(heavens_stdout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
