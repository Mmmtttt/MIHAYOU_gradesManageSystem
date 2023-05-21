#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../src/plugins/TimerPlugin/TimerPlugin.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

class MockGradeManager : public GradeManager {
public:
    MOCK_METHOD0(displayGrades, void());
    // MOCK_METHOD0(queryMaxAndMin, void());
    // MOCK_METHOD0(displayAverageScores, void());
    // MOCK_METHOD0(callback_sortByScores, void());
};

TEST(TimerPluginTest, StartAndStopTest) {
  EXPECT_EQ(80, 80);

    MockGradeManager gradeManager;

    TimerPlugin timerPlugin(1, nullptr);
    timerPlugin.test_setCallback() = std::bind(&GradeManager::displayGrades, &gradeManager);

    // 验证开始定时器时是否创建了新线程并运行
    EXPECT_CALL(gradeManager, displayGrades).Times(2);  // 预期回调函数被调用两次
    timerPlugin.test_execute(&gradeManager);
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();

    // 验证停止定时器后是否停止了回调函数的执行
    EXPECT_CALL(gradeManager, displayGrades).Times(0);  // 预期回调函数不再被调用
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    // 验证再次启动定时器时是否重新创建了新线程并运行
    EXPECT_CALL(gradeManager, displayGrades).Times(2);  // 预期回调函数被调用两次
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();
}

// TEST(TimerPluginTest, SetIntervalTest) {
//     MockGradeManager gradeManager;

//     TimerPlugin timerPlugin(1, nullptr);

//     timerPlugin.test_execute(&gradeManager);
//     timerPlugin.start();

//     // 设置新的时间间隔并验证是否生效
//     timerPlugin.stop();
//     timerPlugin.start();
//     std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//     timerPlugin.stop();
// }

// TEST(TimerPluginTest, SetCallbackTest) {
//     MockGradeManager gradeManager;

//     TimerPlugin timerPlugin(1, nullptr);

//     timerPlugin.test_execute(&gradeManager);
//     timerPlugin.start();

//     // 设置不同的回调函数并验证是否生效
//     EXPECT_CALL(gradeManager, queryMaxAndMin()).Times(2);  // 预期新的回调函数被调用两次
//     timerPlugin.stop();
//     timerPlugin.test_getCallback() = std::bind(&MockGradeManager::queryMaxAndMin, &gradeManager);
//     timerPlugin.start();
//     std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//     timerPlugin.stop();

//     EXPECT_CALL(gradeManager, displayAverageScores()).Times(2);  // 预期新的回调函数被调用两次
//     timerPlugin.stop();
//     timerPlugin.test_getCallback() = std::bind(&MockGradeManager::displayAverageScores, &gradeManager);
//     timerPlugin.start();
//     std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//     timerPlugin.stop();

//     // 验证设置空回调函数时是否正常运行（不会调用回调函数）
//     EXPECT_CALL(gradeManager, displayGrades).Times(0);  // 预期回调函数不会被调用
//     timerPlugin.stop();
//     timerPlugin.test_getCallback() = nullptr;
//     timerPlugin.start();
//     std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//     timerPlugin.stop();
// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// #include <gtest/gtest.h>
// #include "../../../src/Student/Student.h"
// #include <gmock/gmock.h>
// #include "../../../src/plugins/TimerPlugin/TimerPlugin.h"
// #include <iostream>
// #include <windows.h>

// // 测试学生类的成绩获取和修改功能
// // 测试学生类的成绩获取和修改功能
// TEST(StudentTest, GradeAccess)
// {
//     Student student("张三");
//     EXPECT_EQ(student.getName(), "张三");
//     EXPECT_EQ(student.getScore("语文"), -1);
//     EXPECT_EQ(student.getScore("数学"), -1);
//     EXPECT_EQ(student.getScore("英语"), -1);

//     student.setScore("语文",75);
//     student.setScore("数学",95);
//     student.setScore("英语", 88);

//     EXPECT_EQ(student.getScore("语文"), 75);
//     EXPECT_EQ(student.getScore("数学"), 95);
//     EXPECT_EQ(student.getScore("英语"), 88);
// }

// TEST(StudentTest, AddSubject)
// {
//     Student student("李四");
//     student.setScore("化学",67);

//     EXPECT_EQ(student.getScore("化学"), 67);
//     EXPECT_EQ(student.getScore("语文"), -1);
//     EXPECT_EQ(student.getScore("数学"), -1);
//     EXPECT_EQ(student.getScore("英语"), -1);
// }
// // 测试学生类的平均分计算功能
// // TEST(StudentTest, AverageGrade)
// // {
// //     Student student("李四", 80, 90, 85);

// //     double averageGrade = student.calculateAverageGrade();
// //     EXPECT_DOUBLE_EQ(averageGrade, 85.0);
// // }

// // 其他针对学生类的测试用例...

// int main(int argc, char** argv)
// {
//     HMODULE libraryHandle1 = nullptr;
//     libraryHandle1 = LoadLibraryA("../plugins/libdefaultdata.dll");

//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

