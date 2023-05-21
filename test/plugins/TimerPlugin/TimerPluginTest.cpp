#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../src/plugins/TimerPlugin/TimerPlugin.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

class tGradeManager{
    virtual void displayGrades(){}
    virtual void displayAverageScores(){}
    virtual void queryMaxAndMin(){}
    virtual void callback_sortByScores(){}
};

class MockGradeManager : public tGradeManager {
public:
    MOCK_METHOD0(displayGrades, void());
    MOCK_METHOD0(queryMaxAndMin, void());
    MOCK_METHOD0(displayAverageScores, void());
    MOCK_METHOD0(callback_sortByScores, void());
};

TEST(TimerPluginTest, StartAndStopTest) {

    MockGradeManager gradeManager;

    TimerPlugin timerPlugin(1, nullptr);
    timerPlugin.test_setCallback() = std::bind(&MockGradeManager::displayGrades, &gradeManager);

    // 验证开始定时器时是否创建了新线程并运行
    EXPECT_CALL(gradeManager, displayGrades).Times(2);  // 预期回调函数被调用两次
    //timerPlugin.test_execute(&gradeManager);
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

TEST(TimerPluginTest, SetIntervalTest) {
    MockGradeManager gradeManager;

    TimerPlugin timerPlugin(2, nullptr);

    timerPlugin.test_setCallback() = std::bind(&MockGradeManager::displayGrades, &gradeManager);

    EXPECT_CALL(gradeManager, displayGrades).Times(3);  // 预期回调函数
    // 设置新的时间间隔并验证是否生效
    timerPlugin.stop();
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(6500));
    timerPlugin.stop();


    EXPECT_CALL(gradeManager, displayGrades).Times(2);  // 预期回调函数
    timerPlugin.test_setInterval()=1;
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();
}

TEST(TimerPluginTest, SetCallbackTest) {
    MockGradeManager gradeManager;

    TimerPlugin timerPlugin(1, nullptr);


    // 设置不同的回调函数并验证是否生效
    EXPECT_CALL(gradeManager, queryMaxAndMin).Times(2);  // 预期新的回调函数被调用两次
    timerPlugin.stop();
    timerPlugin.test_setCallback() = std::bind(&MockGradeManager::queryMaxAndMin, &gradeManager);
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();

    EXPECT_CALL(gradeManager, displayAverageScores).Times(2);  // 预期新的回调函数被调用两次
    timerPlugin.stop();
    timerPlugin.test_setCallback() = std::bind(&MockGradeManager::displayAverageScores, &gradeManager);
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();

    // 验证设置空回调函数时是否正常运行（不会调用回调函数）
    EXPECT_CALL(gradeManager, displayGrades).Times(0);  // 预期回调函数不会被调用
    timerPlugin.stop();
    timerPlugin.test_setCallback() = nullptr;
    timerPlugin.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    timerPlugin.stop();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
