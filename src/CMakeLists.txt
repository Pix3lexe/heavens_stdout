# Add subdirectories first
add_subdirectory(core)
add_subdirectory(helpers)

# Include all directories so headers can be found
target_include_directories(heavens_stdout PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/helpers
)

# Link with Qt libraries
target_link_libraries(heavens_stdout PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
