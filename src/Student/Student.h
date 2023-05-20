#pragma once

#include <string>
#include <map>

#define default_scores std::map<std::string, int>({{"语文", -1}, {"数学", -1}, {"英语", -1}})

class Student {
public:
    Student(const std::string& name);

    std::string getName() const;

    void setScore(const std::string& subject, int score);

    int getScore(const std::string& subject) const;

    std::map<std::string, int>& getScores() ;

private:
    std::string name;
    std::map<std::string, int> scores;
};
