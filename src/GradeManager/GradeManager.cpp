#include "GradeManager.h"
#include <algorithm>
#include <iostream>

void GradeManager::inputGradesFromConsole() {
    // 根据具体需求实现从命令行输入成绩的逻辑
    // 可以使用 std::cin 获取输入，并创建对应的学生对象并添加到 students 容器中
}

void GradeManager::inputGradesFromFile(const std::string& filename) {
    // 根据具体需求实现从文件读取成绩的逻辑
    // 可以使用文件流(std::ifstream)读取文件内容，并创建对应的学生对象并添加到 students 容器中
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
