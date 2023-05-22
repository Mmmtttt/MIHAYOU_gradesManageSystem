#include "GradeManager.h"
#include <algorithm>



void GradeManager::inputGradesFromConsole() {
    std::string name;
    std::cout<<"请输入学生姓名："<<std::endl;
    std::cin>>name;

    bool found = false;
    for (auto& student : students) {
        if (student.getName() == name) {
            std::cout << "已有该学生,是否修改该学生信息?(y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            if(choice == 'y') {
                InputGradesMenu(student);
                return;
            }
            found = true;
        }
    }
    if(!found) {
        Student newStudent(name);
        InputGradesMenu(newStudent);
        students.push_back(newStudent);
    }
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
    std::istringstream stream(line);
    std::string object;
    objects.clear();
    while (stream >> object) {
        objects.push_back(object);
    }
    objects.erase(objects.begin());  // 删除姓名

    std::vector<std::string> updatedStudents;
    std::vector<std::string> addedStudents;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {continue;} // 跳过空行
        std::istringstream iss(line);
        std::string name;
        iss >> name;
        std::vector<int> scores;
        int score;
        std::string scoreStr;
        while (iss >> scoreStr) {
            if (scoreStr == "缺省") {
                scores.push_back(-1); // 将 "(缺省)" 转换为 -1
            } else {
                int score;
                try {
                    score = std::stoi(scoreStr);
                } catch (const std::exception& e) {
                    score = -1; // 无效的输入，将成绩设置为 -1
                }
                scores.push_back(score);
            }
        }

        // 查找学生并更新成绩
        bool found = false;
        for (auto& student : students) {
            if (student.getName() == name) {
                for (int i = 0; i < objects.size(); i++) {
                    student.setScore(objects[i], scores[i]);
                }
                found = true;
                updatedStudents.push_back(name);
                break;
            }
        }
        if (!found) {
            // 添加学生
            Student newStudent(name);
            for (int i = 0; i < objects.size(); i++) {
                newStudent.setScore(objects[i], scores[i]);
            }
            students.push_back(newStudent);
            addedStudents.push_back(name);
        }
    }

    inputFile.close();

    // 输出更新成绩的学生姓名
    std::cout << "更新成绩的学生姓名：" << std::endl;
    for (const auto& name : updatedStudents) {
        std::cout << name << std::endl;
    }
    std::cout<< std::endl;
    // 输出添加的学生姓名
    std::cout << "添加的学生姓名：" << std::endl;
    for (const auto& name : addedStudents) {
        std::cout << name << std::endl;
    }
}



int GradeManager::queryMaxScore(const std::string& object) {
    int maxScore = -1;

    for (auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            if((scorePair.first==object)&&(scorePair.second!=-1)) 
                maxScore = std::max(maxScore, scorePair.second);
        }
    }

    if(maxScore == -1) {
        std::cout<<"未找到该科目成绩"<<std::endl;
        return -1; // 未找到该科目成绩
    }
    else return maxScore;
}

int GradeManager::queryMinScore(const std::string& object){
    int minScore = 101;

    for (auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            if((scorePair.first==object)&&(scorePair.second!=-1))
                minScore = std::min(minScore, scorePair.second);
        }
    }

    if(minScore == 101) {
        std::cout<<"未找到该科目成绩"<<std::endl;
        return -1; // 未找到该科目成绩
    }
    else return minScore;
}

void GradeManager::sortByScore(const std::string& object) {
    std::sort(students.begin(), students.end(), [object](const Student& s1, const Student& s2) {
        int score1 = s1.getScore(object);
        int score2 = s2.getScore(object);
        return score1 > score2;
    });
    displayGrades();
}

void GradeManager::displayGrades(){
    std::ofstream outputFile(storeFile, std::ofstream::trunc); // 清空文件内容并打开文件用于写入
    if (!outputFile.is_open()) {
        std::cout << "无法打开文件 ../grades.txt" << std::endl;
        return;
    }

    std::cout<<std::setw(12)<<"姓名";
    outputFile << "姓名 ";
    if(students.size()==0){std::cout<<"无信息"<<std::endl;return;}
    for(const auto& object : objects) {
        std::cout <<std::setw(12)<< object;
        outputFile << object << " ";
    }

    std::cout<<std::endl;  
    outputFile << std::endl;

    for (auto& student : students) {
        std::cout<<std::setw(12)<<student.getName();
        outputFile << student.getName() << " ";

        for (const auto& object : objects) {
            auto it = student.getScores().find(object);
            if (it == student.getScores().end()) student.setScore(object, -1); // 未找到该科目成绩，设置为 -1

            int score=student.getScore(object);
            if(score==-1){
                std::cout <<std::setw(12)<<"缺省";
            }
            else std::cout <<std::setw(10)<< score;
            
            outputFile << score << " ";
        }

        std::cout << std::endl;
        outputFile << std::endl;
    }

    outputFile.close();
}


void GradeManager::displayAverageScores(){
    std::map<std::string, double> averageScores;
    std::map<std::string, int> subjectCount;

    for (auto& student : students) {
        for (const auto& scorePair : student.getScores()) {
            const std::string& subject = scorePair.first;
            int score = scorePair.second;
            if(score == -1) continue;
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

void GradeManager::modifyScore() {
    std::string name;
    std::cout<<"请输入学生姓名："<<std::endl;
    std::cin>>name;

    bool found = false;
    for (auto& student : students) {
        if (student.getName() == name) {
            InputGradesMenu(student);
            found = true;
            return;
        }
    }
    if(!found) {
        std::cout << "未找到该学生,是否创建该学生信息?(y/n)" << std::endl;
        char choice;
        std::cin >> choice;
        if(choice == 'y') {
            Student newStudent(name);
            InputGradesMenu(newStudent);
            students.push_back(newStudent);
        }
    }
}

void GradeManager::InputGradesMenu(Student& student) {
    getchar();
    for (auto& object : objects) {
        std::cout << "科目: " << object << "   初始成绩(缺省值为-1): " << student.getScore(object);
        std::cout << " 输入新成绩(输入回车跳过): ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue; // 用户输入回车，保持初始值
        }

        int score;
        try {
            score = std::stoi(input);
        } catch (const std::exception& e) {
            continue; // 无效的输入，保持初始值
        }

        if (score >= 0 && score <= 100) {
            student.setScore(object, score);
        }
    }
}

std::vector<Student>& GradeManager::getStudents(){
    return students;
}