#include <gtest/gtest.h>
#include "../../src/Student/Student.h"

// 测试学生类的成绩获取和修改功能
TEST(StudentTest, GradeAccess)
{
    Student student("张三");
    EXPECT_EQ(student.getName(), "张三");
    EXPECT_EQ(student.getScore("语文"), -1);
    EXPECT_EQ(student.getScore("数学"), -1);
    EXPECT_EQ(student.getScore("英语"), -1);

    student.setScore("语文",75);
    student.setScore("数学",95);
    student.setScore("英语", 88);

    EXPECT_EQ(student.getScore("语文"), 75);
    EXPECT_EQ(student.getScore("数学"), 95);
    EXPECT_EQ(student.getScore("英语"), 88);
}

TEST(StudentTest, AddSubject)
{
    Student student("李四");
    student.setScore("化学",67);

    EXPECT_EQ(student.getScore("化学"), 67);
    EXPECT_EQ(student.getScore("语文"), -1);
    EXPECT_EQ(student.getScore("数学"), -1);
    EXPECT_EQ(student.getScore("英语"), -1);
}
// 测试学生类的平均分计算功能
// TEST(StudentTest, AverageGrade)
// {
//     Student student("李四", 80, 90, 85);

//     double averageGrade = student.calculateAverageGrade();
//     EXPECT_DOUBLE_EQ(averageGrade, 85.0);
// }

// 其他针对学生类的测试用例...

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
