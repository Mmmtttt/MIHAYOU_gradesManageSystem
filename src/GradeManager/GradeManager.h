#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include "../Student/Student.h"

#define storeFile "../grades.txt"

class GradeManager {
private:
    //基础组件
    int queryMaxScore(const std::string& object);
    int queryMinScore(const std::string& object);
    void sortByScore(const std::string& object);
    void InputGradesMenu(Student& student);


public: //功能接口
    void inputGradesFromConsole();
    void loadGradesFromFile(const std::string& filename);
    void displayGrades() ;
    void displayAverageScores();
    void modifyScore();
    void queryMaxAndMin(){
        if(objects.size()==0){std::cout<<"没有信息"<<std::endl;return;}
            for(const auto& object:objects){
                std::cout << object<< ": ";
                std::cout << "最高分：" << queryMaxScore(object) << std::endl;
                std::cout << "最低分：" << queryMinScore(object) << std::endl;
            }
    }
    void sortByScores(){
        std::cout << "按成绩排序,请输入科目" ;
        std::string subject;
        std::cin >> subject;
        std::cout <<std::endl;
        sortByScore(subject);
    }
    void callback_sortByScores(){
        if(callback_sortByScores_varaible==""){
            std::cout<<"未设置科目"<<std::endl;
            return;
        }
        sortByScore(callback_sortByScores_varaible);
    }
    std::vector<std::string> objects;
    std::vector<Student> getStudents() const;
    std::string callback_sortByScores_varaible;

private:
    std::vector<Student> students;
};

#endif // GRADEMANAGER_H
