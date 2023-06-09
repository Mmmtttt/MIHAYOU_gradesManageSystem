#include <iostream>
#include "GradeManager/GradeManager.h"
//#include <dlfcn.h>
#include <windows.h>
#include "./plugins/PluginInterface.h"
#include <iomanip>

// 定义控制台颜色

const int GREEN = 10;
const int YELLOW = 14;
const int RED = 12;
const int RESET = 7;


#define inputFile "../input.txt"

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




//typedef void (*PluginFunction)();
typedef std::unique_ptr<PluginInterface> (*Plugin_ptr)();//创建函数指针，返回类型为 Plugin接口 的智能指针

int main() {

    //void* libHandle = nullptr;
    HMODULE libraryHandle1 = nullptr;
    HMODULE libraryHandle2 = nullptr;
    std::unique_ptr<PluginInterface> temp_obj1;
    std::unique_ptr<PluginInterface> temp_obj2;
    
    GradeManager gradeManager;
    gradeManager.loadGradesFromFile(storeFile);


    while (true) {
        
        // Windows控制台颜色设置
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // 边框颜色
        SetConsoleTextAttribute(hConsole, 11); // 亮青色
        std::cout << "╔══════════════════════════════╗" << std::endl;
        // 字体颜色
        SetConsoleTextAttribute(hConsole, 14); // 黄色
        std::cout << "║         成绩管理系统         ║" << std::endl;
        // 边框颜色
        SetConsoleTextAttribute(hConsole, 11); // 亮青色
        std::cout << "╠══════════════════════════════╣" << std::endl;
        SetConsoleTextAttribute(hConsole, 14); // 黄色

        std::cout <<"║ 1.  加载“寻找缺省数据模块” ║" <<std::endl;
        std::cout <<"║ 2.  卸载“寻找缺省数据模块” ║" <<std::endl;
        std::cout <<"║ 3.  加载“定时器模块”       ║" <<std::endl;
        std::cout << "║ 4.  卸载“定时器模块”       ║" <<std::endl;
        std::cout << "║ 5.  寻找缺省数据             ║" <<std::endl;
        std::cout << "║ 6.  设置定时器               ║" <<std::endl;
        std::cout << "║ 7.  查询科目最高分与最低分   ║" <<std::endl;
        std::cout << "║ 8.  按成绩排序               ║" <<std::endl;
        std::cout << "║ 9.  各科目平均分             ║" <<std::endl;
        std::cout << "║ 10. 修改成绩                 ║" <<std::endl;
        std::cout << "║ 11. 输入成绩                 ║" <<std::endl;
        std::cout << "║ 12. 显示所有信息             ║" <<std::endl;
        std::cout << "║ 0.  Quit                     ║" <<std::endl;
        std::cout << "╠══════════════════════════════╣" << std::endl;

        SetConsoleTextAttribute(hConsole, 7); // 恢复默认颜色
        std::cout << "输入选项： ";
        std::cout << std::endl;

        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                //libHandle = dlopen("./plugin/libdefaultdata.so", RTLD_LAZY);
                libraryHandle1 = LoadLibraryA("./plugins/libdefaultdata.dll");
                //if (!libHandle) {
                if (!libraryHandle1) {
                    //std::cerr << "Failed to load libdefaultdata.so: " << dlerror() << std::endl;
                    std::cerr << "Failed to load libdefaultdata.dll: " << std::endl;
                } else {
                    //Plugin_ptr create_Plugin =Plugin_ptr(dlsym(libHandle, "create_Plugin"));
                    Plugin_ptr create_Plugin =Plugin_ptr(GetProcAddress(libraryHandle1, "create_Plugin"));
                    temp_obj1 = create_Plugin();
                    if(temp_obj1){
                        std::cout << "libdefaultdata.dll loaded." << std::endl;
                        
                    }
                    else 
                        std::cout << "temp_obj is null." << std::endl;
                }
                break;
            }
            case 2: {
                if (libraryHandle1) {
                    temp_obj1.reset();
                    //dlclose(libHandle);
                    FreeLibrary(libraryHandle1);
                    //libHandle=nullptr;
                    libraryHandle1=nullptr;
                    
                    std::cout << "libdefaultdata.dll unloaded." << std::endl;
                } else {
                    std::cout << "libdefaultdata.dll is not loaded." << std::endl;
                }
                break;
            }
            case 3: {
                //libHandle = dlopen("./plugin/libtimer.so", RTLD_LAZY);
                libraryHandle2 = LoadLibraryA("./plugins/libtimer.dll");
                //if (!libHandle) {
                if (!libraryHandle2) {
                    //std::cerr << "Failed to load libtimer.so: " << dlerror() << std::endl;
                    std::cerr << "Failed to load libtimer.dll: " << std::endl;
                } else {
                    //Plugin_ptr create_Plugin =Plugin_ptr(dlsym(libHandle, "create_Plugin"));
                    Plugin_ptr create_Plugin =Plugin_ptr(GetProcAddress(libraryHandle2, "create_Plugin"));
                    temp_obj2 = create_Plugin();
                    if(temp_obj2){
                        std::cout << "libtimer.dll loaded." << std::endl;
                        
                    }
                    else 
                        std::cout << "temp_obj is null." << std::endl;
                }
                break;
            }
            case 4: {
                if (libraryHandle2) {
                    temp_obj2.reset();
                    //dlclose(libHandle);
                    FreeLibrary(libraryHandle2);
                    libraryHandle2=nullptr;
                    //libHandle=nullptr;
                    
                    std::cout << "libtimer.dll unloaded." << std::endl;
                } else {
                    std::cout << "libtimer.dll is not loaded." << std::endl;
                }
                break;
            }
            case 5: {
                if (temp_obj1) {
                    temp_obj1->execute(&gradeManager);
                } else {
                    std::cout << "libdefaultdata.dll is not loaded." << std::endl;
                }
                break;
            }
            case 6: {
                if (temp_obj2) {
                    temp_obj2->execute(&gradeManager);
                } else {
                    std::cout << "libtimer.dll is not loaded." << std::endl;
                }
                break;
            }
            case 7:  {               
                gradeManager.queryMaxAndMin();
                break;
            }
            case 8: {
                gradeManager.sortByScores();
                //gradeManager.displayGrades();
                break;
            }
            case 9: {
                std::cout << "各科目平均分：" << std::endl;
                gradeManager.displayAverageScores();
                break;
            }
            case 10: {
                std::cout << "修改成绩：" << std::endl;
                gradeManager.modifyScore();
                gradeManager.displayGrades();
                break;
            }
            case 11: {
                std::cout << "输入成绩：" << std::endl;
                std::cout<<"选择输入方式: 1.手动  2.文件"<<std::endl;
                int choice;
                std::cin>>choice;
                if(choice==1){
                    gradeManager.inputGradesFromConsole();
                    gradeManager.displayGrades();
                }
                else if(choice==2)
                    gradeManager.loadGradesFromFile(inputFile);
                break;
            }
            case 12: {
                gradeManager.displayGrades();
                break;
            }
            case 0:
                return 0;
            default:{std::cout << "请重新输入." << std::endl;break;}
                
        }
        std::cout<<"输入回车继续"<<std::endl;
        getchar();
        getchar();
        system("cls");
    }
}



