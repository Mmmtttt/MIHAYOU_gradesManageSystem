#include <iostream>
#include "GradeManager/GradeManager.h"
#include <dlfcn.h>
#include "../plugins/plugininterface.h"

// int main() {
//     GradeManager gradeManager;

//     // 录入成绩示例
//     gradeManager.inputGradesFromConsole();
//     // 或者从文件读取成绩
    // gradeManager.inputGradesFromFile("grades.txt");

    // 查询成绩示例
    // std::cout << "科目最高分：" << gradeManager.queryMaxScore() << std::endl;
    // std::cout << "科目最低分：" << gradeManager.queryMinScore() << std::endl;

    // std::cout << "按语文成绩排序：" << std::endl;
    // gradeManager.sortByChineseScore();
    // gradeManager.displayGrades();

    // std::cout << "各科目平均分：" << std::endl;
    // gradeManager.displayAverageScores();

    // // 修改成绩示例
    // gradeManager.modifyScore("张三", "数学", 90);




typedef void (*PluginFunction)();
typedef std::unique_ptr<PluginInterface> (*Plugin)();

int main() {
    void* libHandle = nullptr;
    std::unique_ptr<PluginInterface> temp_obj;

    while (true) {
        int choice;
        std::cout << "1. Load Library 1" << std::endl;
        std::cout << "2. Unload Library 1" << std::endl;
        std::cout << "3. Load Library 2" << std::endl;
        std::cout << "4. Unload Library 2" << std::endl;
        std::cout << "5. Call Function 1" << std::endl;
        std::cout << "6. Call Function 2" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                libHandle = dlopen("./plugin/libfun1.so", RTLD_LAZY);
                if (!libHandle) {
                    std::cerr << "Failed to load library 1: " << dlerror() << std::endl;
                } else {
                    Plugin create_Plugin =Plugin(dlsym(libHandle, "create_Plugin"));
                    temp_obj = create_Plugin();
                    if(temp_obj){
                        std::cout << "Library 1 loaded." << std::endl;
                        temp_obj->load();
                    }
                    else 
                        std::cout << "temp_obj is null." << std::endl;
                }
                break;
            }
            case 2: {
                if (temp_obj) {
                    temp_obj->unload();
                    dlclose(libHandle);
                    libHandle=nullptr;
                    temp_obj.release();
                    std::cout << "Library 1 unloaded." << std::endl;
                } else {
                    std::cout << "Library is not loaded." << std::endl;
                }
                break;
            }
            case 3: {
                libHandle = dlopen("./plugin/libfun2.so", RTLD_LAZY);
                if (!libHandle) {
                    std::cerr << "Failed to load library 2: " << dlerror() << std::endl;
                } else {
                    Plugin create_Plugin =Plugin(dlsym(libHandle, "create_Plugin"));
                    temp_obj = create_Plugin();
                    if(temp_obj){
                        std::cout << "Library 2 loaded." << std::endl;
                        temp_obj->load();
                    }
                    else 
                        std::cout << "temp_obj is null." << std::endl;
                }
                break;
            }
            case 4: {
                if (temp_obj) {
                    temp_obj->unload();
                    dlclose(libHandle);
                    libHandle=nullptr;
                    temp_obj.release();
                    std::cout << "Library 2 unloaded." << std::endl;
                } else {
                    std::cout << "Library is not loaded." << std::endl;
                }
                break;
            }
            case 5: {
                if (temp_obj) {
                    temp_obj->callFun1();
                } else {
                    std::cout << "No library is loaded." << std::endl;
                }
                break;
            }
            case 6: {
                if (temp_obj) {
                    temp_obj->callFun2();
                } else {
                    std::cout << "No library is loaded." << std::endl;
                }
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}



