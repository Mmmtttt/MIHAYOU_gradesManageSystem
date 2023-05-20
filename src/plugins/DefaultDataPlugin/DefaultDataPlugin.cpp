#include "DefaultDataPlugin.h"

#include <iostream>

void DefaultDataPlugin::getDfaultData(GradeManager* grademanager_ptr) const {
    for(auto& student : grademanager_ptr->getStudents()) {
        for(auto& subject : grademanager_ptr->objects) {
            if(student.getScore(subject) == -1) {
                std::cout<<"缺省数据："<<student.getName()<<" "<<subject<<std::endl;
            }
        }
    }
}


void DefaultDataPlugin::execute(GradeManager* grademanager_ptr) {
    std::cout << "查找缺省数据(插件功能)" << std::endl;
    getDfaultData(grademanager_ptr);
}
