#include "Student.h"

Student::Student(const std::string& name) : name(name) , scores(default_scores) {}

std::string Student::getName() const {
    return name;
}

int Student::getScore(const std::string& subject) const {
    auto it = scores.find(subject);
    if (it != scores.end()) {
        return it->second;
    }
    return -1;  // 返回一个无效的分数值表示未找到该科目的成绩
}

void Student::setScore(const std::string& subject, int score) {
    scores[subject] = score;
}

std::map<std::string, int>& Student::getScores() {
    return scores;
}