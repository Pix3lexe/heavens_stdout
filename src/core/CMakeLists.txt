target_sources(heavens_stdout PRIVATE
    heavens_stdout.h
    heavens_stdout.cpp
    scalableWidget.h
    scalableWidget.cpp
    main_widget.ui
    mainScalableWidget.h
    mainScalableWidget.cpp
)

target_include_directories(heavens_stdout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
