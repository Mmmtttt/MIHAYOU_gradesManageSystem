add_library(GradeManager
    GradeManager.cpp
    GradeManager.h
)

#设置GradeManager为位置无关选项，因为两个动态链接库都要调用GradeManager中的函数
set_target_properties(GradeManager PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(GradeManager Student)
