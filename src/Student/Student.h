#pragma once

#include <string>
#include <map>

class Student {
public:
    Student(const std::string& name);

    std::string getName() const;

    void setScore(const std::string& subject, int score);

    int getScore(const std::string& subject) const;

    std::map<std::string, int> getScores() const;

private:
    std::string name;
    std::map<std::string, int> scores;
};
