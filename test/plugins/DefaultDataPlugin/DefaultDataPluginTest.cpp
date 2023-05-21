#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../src/plugins/DefaultDataPlugin/DefaultDataPlugin.h"
#include "../../../src/GradeManager/GradeManager.h"

// 测试 DefaultDataPlugin 的功能
TEST(DefaultDataPluginTest, ExecuteTest) {
    // 创建 GradeManagerMock 对象
    GradeManager grademanager;
    //create plugin
    std::unique_ptr obj_temp=create_Plugin();

    Student a("Alice");
    Student b("Bob");
    a.setScore("语文", 90);a.setScore("数学", 87);a.setScore("英语", -1);
    b.setScore("语文", 67);b.setScore("数学", -1);b.setScore("英语", 68);


    grademanager.getStudents().push_back(a);
    grademanager.getStudents().push_back(b);

    // 调用函数并捕获输出
    testing::internal::CaptureStdout();
    
    obj_temp->execute(&grademanager);

    std::string output = testing::internal::GetCapturedStdout();
    std::istringstream iss(output);
    std::string line;

  // 验证表头
    std::getline(iss, line);


    std::getline(iss, line);
    EXPECT_EQ(line,"缺省数据：Alice 英语");
    std::getline(iss, line);
    EXPECT_EQ(line,"缺省数据：Bob 数学");

}



int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

