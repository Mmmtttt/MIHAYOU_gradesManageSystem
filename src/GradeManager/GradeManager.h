#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Student/Student.h"

class GradeManager {
public:
    void inputGradesFromConsole();
    void loadGradesFromFile(const std::string& filename);
    int queryMaxScore(const std::string& object);
    int queryMinScore(const std::string& object);
    void sortByScore(const std::string& object);
    void displayGrades() ;
    void displayAverageScores();
    void modifyScore();
    void InputGradesMenu(Student& student);

private:
    std::vector<Student> students;
};

#endif // GRADEMANAGER_H
