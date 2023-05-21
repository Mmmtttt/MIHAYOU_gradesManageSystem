

# 包含 Google Test 框架
add_subdirectory(test_frame)

# 构建测试可执行文件
add_executable(StudentTests
  Student/StudentTest.cpp
)
add_executable(GradeManagerTests
  GradeManager/GradeManagerTest.cpp
)
add_executable(DefaultDataPluginTests
  plugins/DefaultDataPlugin/DefaultDataPluginTest.cpp
)
add_executable(TimerPluginTests
  plugins/TimerPlugin/TimerPluginTest.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/bin/plugins)

# 链接测试可执行文件和 Google Test 框架
target_link_libraries(StudentTests
  gtest_main
  gmock_main
  Student
)
target_link_libraries(GradeManagerTests
  gtest_main
  gmock_main
  GradeManager
)
target_link_libraries(DefaultDataPluginTests
  gtest_main
  gmock_main
  DefaultDataPlugin
  Student
)
target_link_libraries(TimerPluginTests
  gtest_main
  gmock_main
  TimerPlugin
  Student
)


set_target_properties(DefaultDataPluginTests PROPERTIES BUILD_RPATH "${CMAKE_SOURCE_DIR}/bin/plugins")
set_target_properties(TimerPluginTests PROPERTIES BUILD_RPATH "${CMAKE_SOURCE_DIR}/bin/plugins")



set_target_properties(StudentTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/test)
set_target_properties(GradeManagerTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/test)
set_target_properties(DefaultDataPluginTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/test)
set_target_properties(TimerPluginTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/test)