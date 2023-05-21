cmake_minimum_required(VERSION 3.12)
project(GradeManagementSystem)

# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#debug
#set(CMAKE_BUILD_TYPE DEBUG)


if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

  add_executable(GradeManagementSystem
    src/main_L.cpp
  )

elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  # 添加可执行文件
  add_executable(GradeManagementSystem
    src/main_W.cpp
  )

else()
 
	message("current platform: unkonw ")
 
endif()



# 设置构建输出路径
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
# 设置编译输出路径为bin目录下的plugin文件夹
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/plugins)

set_target_properties(GradeManagementSystem PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


# 添加子目录
add_subdirectory(src/Student)
add_subdirectory(src/GradeManager)
add_subdirectory(src/plugins)

# 添加静态基础链接库
target_link_libraries(GradeManagementSystem Student GradeManager)

# 添加测试目录
#add_subdirectory(test)

