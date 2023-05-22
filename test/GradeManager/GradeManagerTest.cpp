#include <gtest/gtest.h>
#include "../../src/GradeManager/GradeManager.h"



TEST(GradeManagerTest, LoadGradesFromFileTest) {
  GradeManager gradeManager;

  // 创建一个临时的测试文件
  std::ofstream file("test_grades.txt");
  file << "姓名 语文 数学 英语\n";
  file << "Bob 80 75 85\n";
  file << "Alice 90 85 95\n";
  file.close();

  // 调用函数
  gradeManager.loadGradesFromFile("test_grades.txt");

  // 验证学生是否正确加载
  std::vector<Student> students = gradeManager.getStudents();
  ASSERT_EQ(students.size(), 2);
  EXPECT_EQ(students[0].getName(), "Bob");
  EXPECT_EQ(students[0].getScore("语文"), 80);
  EXPECT_EQ(students[0].getScore("数学"), 75);
  EXPECT_EQ(students[0].getScore("英语"), 85);
  EXPECT_EQ(students[1].getName(), "Alice");
  EXPECT_EQ(students[1].getScore("语文"), 90);
  EXPECT_EQ(students[1].getScore("数学"), 85);
  EXPECT_EQ(students[1].getScore("英语"), 95);

  // 删除临时的测试文件
  std::remove("test_grades.txt");
}

// 测试 displayGrades() 函数是否正确显示成绩
TEST(GradeManagerTest, DisplayGradesTest) {
  GradeManager gradeManager;

  // 创建两个学生并设置成绩
  Student student1("Alice");
  student1.setScore("语文", 90);
  student1.setScore("数学", 85);
  student1.setScore("英语", 95);
  gradeManager.getStudents().push_back(student1);

  Student student2("Bob");
  student2.setScore("语文", 80);
  student2.setScore("数学", 75);
  student2.setScore("英语", 85);
  gradeManager.getStudents().push_back(student2);

  // 调用函数并捕获输出
  testing::internal::CaptureStdout();
  gradeManager.displayGrades();
  std::string output = testing::internal::GetCapturedStdout();

  // 验证输出是否正确
  std::istringstream iss(output);
  std::string line;

  // 验证表头
  std::getline(iss, line);
  EXPECT_EQ(line, "      姓名      语文      数学      英语");

  // 验证第一位学生的成绩
  std::getline(iss, line);
  EXPECT_EQ(line, "       Alice        90        85        95");

  // 验证第二位学生的成绩
  std::getline(iss, line);
  EXPECT_EQ(line, "         Bob        80        75        85");
}

// 测试 displayAverageScores() 函数是否正确显示平均成绩
TEST(GradeManagerTest, DisplayAverageScoresTest) {
  GradeManager gradeManager;

  // 创建两个学生并设置成绩
  Student student1("Alice");
  student1.setScore("语文", 90);
  student1.setScore("数学", 85);
  student1.setScore("英语", 95);
  gradeManager.getStudents().push_back(student1);

  Student student2("Bob");
  student2.setScore("语文", 80);
  student2.setScore("数学", 75);
  student2.setScore("英语", 85);
  gradeManager.getStudents().push_back(student2);

  // 调用函数并捕获输出
  testing::internal::CaptureStdout();
  gradeManager.displayAverageScores();
  std::string output = testing::internal::GetCapturedStdout();

  // 验证输出是否正确
  std::istringstream iss(output);
  std::string line;


  // 验证第一科目的平均分
  std::getline(iss, line);
  EXPECT_EQ(line, "数学 平均分: 80");

  // 验证第二科目的平均分
  std::getline(iss, line);
  EXPECT_EQ(line, "英语 平均分: 90");
  
  // 验证第三科目的平均分
  std::getline(iss, line);
  EXPECT_EQ(line, "语文 平均分: 85");
}

// 测试 queryMaxAndMin() 函数是否正确显示最高分和最低分
TEST(GradeManagerTest, QueryMaxAndMinTest) {
  GradeManager gradeManager;

  // 创建两个学生并设置成绩
  Student student1("Alice");
  student1.setScore("语文", 90);
  student1.setScore("数学", 85);
  student1.setScore("英语", 95);
  gradeManager.getStudents().push_back(student1);

  Student student2("Bob");
  student2.setScore("语文", 80);
  student2.setScore("数学", 75);
  student2.setScore("英语", 85);
  gradeManager.getStudents().push_back(student2);

  // 调用函数并捕获输出
  testing::internal::CaptureStdout();
  gradeManager.queryMaxAndMin();
  std::string output = testing::internal::GetCapturedStdout();

  // 验证输出是否正确
  std::istringstream iss(output);
  std::string line;

  // 验证第一科目的最高分和最低分
  std::getline(iss, line);
  EXPECT_EQ(line, "语文: 最高分：90");
  std::getline(iss, line);
  EXPECT_EQ(line, "最低分：80");

  // 验证第二科目的最高分和最低分
  std::getline(iss, line);
  EXPECT_EQ(line, "数学: 最高分：85");
  std::getline(iss, line);
  EXPECT_EQ(line, "最低分：75");
  
  // 验证第三科目的最高分和最低分
  std::getline(iss, line);
  EXPECT_EQ(line, "英语: 最高分：95");
  std::getline(iss, line);
  EXPECT_EQ(line, "最低分：85");

}

// 测试 sortByScores() 函数是否正确排序成绩
TEST(GradeManagerTest, SortByScoresTest) {
  GradeManager gradeManager;

  // 创建两个学生并设置成绩
  Student student1("Alice");
  student1.setScore("语文", 90);
  student1.setScore("数学", 75);
  student1.setScore("英语", 95);
  gradeManager.getStudents().push_back(student1);

  Student student2("Bob");
  student2.setScore("语文", 80);
  student2.setScore("数学", 85);
  student2.setScore("英语", 85);
  gradeManager.getStudents().push_back(student2);

  Student student3("Jack");
  student3.setScore("语文", 60);
  student3.setScore("数学", 65);
  student3.setScore("英语", 100);
  gradeManager.getStudents().push_back(student3);

  // 模拟用户输入
  std::istringstream input("数学\n");
  std::streambuf* old_stdin = std::cin.rdbuf(input.rdbuf());

  // 调用函数并捕获输出
  testing::internal::CaptureStdout();
  gradeManager.sortByScores();
  std::string output = testing::internal::GetCapturedStdout();


    // 恢复标准输入
  std::cin.rdbuf(old_stdin);

  // 验证输出是否正确
  std::istringstream iss(output);
  std::string line;

  // 验证表头
  std::getline(iss, line);
  std::getline(iss, line);
  EXPECT_EQ(line, "      姓名      语文      数学      英语");

  // 验证第一位学生的成绩
  std::getline(iss, line);
  EXPECT_EQ(line, "         Bob        80        85        85");

  // 验证第二位学生的成绩
  std::getline(iss, line);
  EXPECT_EQ(line, "       Alice        90        75        95");
  
  // 验证第三位学生的成绩
  std::getline(iss, line);
  EXPECT_EQ(line, "        Jack        60        65       100");
}

// 测试 modifyScore() 函数是否正确修改成绩
TEST(GradeManagerTest, ChangeScoreTest) {
  GradeManager gradeManager;

  // 创建一个学生并设置成绩
  Student student("Alice");
  student.setScore("语文", 90);
  student.setScore("数学", 85);
  student.setScore("英语", 95);
  gradeManager.getStudents().push_back(student);

  // 模拟用户输入
  std::istringstream input("Alice\n80 \n \n");
  std::streambuf* old_stdin = std::cin.rdbuf(input.rdbuf()); 

  // 调用函数修改成绩
  gradeManager.modifyScore();

  // 恢复标准输入
  std::cin.rdbuf(old_stdin);

  // 验证成绩是否正确修改
  Student modifiedStudent = gradeManager.getStudents().front();
  EXPECT_EQ(modifiedStudent.getScore("数学"), 80);
}



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
