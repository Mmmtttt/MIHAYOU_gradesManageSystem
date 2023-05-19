add_library(DefaultDataPlugin SHARED
    DefaultDataPlugin/DefaultDataPlugin.cpp
    DefaultDataPlugin/DefaultDataPlugin.h
)

add_library(TimerPlugin SHARED
    TimerPlugin/TimerPlugin.cpp
    TimerPlugin/TimerPlugin.h
)

set_target_properties(DefaultDataPlugin PROPERTIES OUTPUT_NAME "defaultdata")
set_target_properties(TimerPlugin PROPERTIES OUTPUT_NAME "timer")

set_target_properties(DefaultDataPlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin/plugins)
set_target_properties(TimerPlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin/plugins)
