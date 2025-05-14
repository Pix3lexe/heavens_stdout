add_library(generatorlib
    generator.cpp
)

target_include_directories(generatorlib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(generatorlib
    PUBLIC
    Qt6::Core
)
