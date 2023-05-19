#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <string>
#include "Student/Student.h"

class GradeManager {
public:
    void inputGradesFromConsole();
    void inputGradesFromFile(const std::string& filename);
    int queryMaxScore() const;
    int queryMinScore() const;
    void sortByChineseScore();
    void displayGrades() const;
    void displayAverageScores() const;
    void modifyScore(const std::string& name, const std::string& subject, int score);

private:
    std::vector<Student> students;
};

#endif // GRADEMANAGER_H
