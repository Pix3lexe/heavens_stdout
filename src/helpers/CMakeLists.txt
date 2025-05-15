target_sources(heavens_stdout PRIVATE
    constants.h
    generator.h
    generator.cpp
)

target_include_directories(heavens_stdout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
