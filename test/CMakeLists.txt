cmake_minimum_required(VERSION 3.5)
project(GradeManagementSystemTests)

# 设置编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含 Google Test 框架
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

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

# 链接测试可执行文件和 Google Test 框架
target_link_libraries(StudentTests
  gtest_main
  Student
)
target_link_libraries(GradeManagerTests
  gtest_main
  GradeManager
)
target_link_libraries(DefaultDataPluginTests
  gtest_main
  DefaultDataPlugin
)
target_link_libraries(TimerPluginTests
  gtest_main
  TimerPlugin
)
