target_sources(heavens_stdout PRIVATE
    talkModeWidget.h
    talkModeWidget.cpp
    talkModeWidget.ui
    stringSearchModeWidget.h
    stringSearchModeWidget.cpp
    stringSearchModeWidget.ui
)

target_include_directories(heavens_stdout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
