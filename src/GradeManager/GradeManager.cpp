#include "GradeManager.h"
#include <algorithm>
#include <iostream>

// 在 GradeManager 类中添加成员函数 updateGradesFromFile
void GradeManager::updateGradesFromFile(const std::string& filename) {
    // 调用 loadGradesFromFile 函数加载成绩数据并更新学生的成绩
    loadGradesFromFile(filename);
}

// 创建新的 loadGradesFromFile 函数用于从txt文件中加载成绩数据
void GradeManager::loadGradesFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "无法打开文件 " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(inputFile, line);  // 读取表头
    // 假设表头为 "姓名 语文 数学 英语"

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name;
        int chinese, math, english;

        if (!(iss >> name >> chinese >> math >> english)) {
            std::cout << "文件格式错误：" << line << std::endl;
            continue;
        }

        // 处理学生的某课成绩可能为空的情况
        // if (chinese == -1) {
        //     chinese = 0;  // 将缺省成绩置为0或其他默认值
        // }
        // if (math == -1) {
        //     math = 0;  // 将缺省成绩置为0或其他默认值
        // }
        // if (english == -1) {
        //     english = 0;  // 将缺省成绩置为0或其他默认值
        // }

        // 查找学生并更新成绩
        bool found = false;
        for (auto& student : students) {
            if (student.getName() == name) {
                student.setScore("语文", chinese);
                student.setScore("数学", math);
                student.setScore("英语", english);
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "找不到学生：" << name << std::endl;
        }
    }

    inputFile.close();
}


int GradeManager::queryMaxScore() const {
    int maxScore = -1;

    for (const auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            maxScore = std::max(maxScore, scorePair.second);
        }
    }

    return maxScore;
}

int GradeManager::queryMinScore() const {
    int minScore = std::numeric_limits<int>::max();

    for (const auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            minScore = std::min(minScore, scorePair.second);
        }
    }

    return minScore;
}

void GradeManager::sortByChineseScore() {
    std::sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
        int score1 = s1.getScore("语文");
        int score2 = s2.getScore("语文");
        return score1 < score2;
    });
}

void GradeManager::displayGrades() const {
    for (const auto& student : students) {
        std::cout << "姓名: " << student.getName() << std::endl;
        for (const auto& scorePair : student.getScores()) {
            std::cout << scorePair.first << ": " << scorePair.second << " ";
        }
        std::cout << std::endl;
    }
}

void GradeManager::displayAverageScores() const {
    std::map<std::string, double> averageScores;
    std::map<std::string, int> subjectCount;

    for (const auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            const std::string& subject = scorePair.first;
            int score = scorePair.second;
            averageScores[subject] += score;
            subjectCount[subject]++;
        }
    }

    for (const auto& entry : averageScores) {
        const std::string& subject = entry.first;
        double average = entry.second / static_cast<double>(subjectCount[subject]);
        std::cout << subject << " 平均分: " << average << std::endl;
    }
}

void GradeManager::modifyScore(const std::string& name, const std::string& subject, int score) {
    bool found = false;
    for (auto& student : students) {
        if (student.getName() == name) {
            student.setScore(subject, score);
            found = true;
            return;
        }
    }
    if(!found) {
        std::cout << "未找到该学生" << std::endl;
    }
}
