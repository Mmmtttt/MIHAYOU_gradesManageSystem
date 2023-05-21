add_library(DefaultDataPlugin SHARED
    DefaultDataPlugin/DefaultDataPlugin.cpp
    DefaultDataPlugin/DefaultDataPlugin.h
)

# 将插件和GradeManager库链接在一起
target_link_libraries(DefaultDataPlugin GradeManager)
set_target_properties(DefaultDataPlugin PROPERTIES LINKER_LANGUAGE CXX)

add_library(TimerPlugin SHARED
    TimerPlugin/TimerPlugin.cpp
    TimerPlugin/TimerPlugin.h
)

# 将插件和GradeManager库链接在一起
target_link_libraries(TimerPlugin GradeManager)
set_target_properties(TimerPlugin PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(DefaultDataPlugin PROPERTIES OUTPUT_NAME "defaultdata")
set_target_properties(TimerPlugin PROPERTIES OUTPUT_NAME "timer")

set_target_properties(DefaultDataPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins)
set_target_properties(TimerPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins)
