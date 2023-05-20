#include <iostream>
#include "TimerPlugin.h"

TimerPlugin::TimerPlugin(int intervalInSeconds, std::function<void()> callback)
    : interval(intervalInSeconds), running(false) {}

void TimerPlugin::start() {
    if (!running) {
        running = true;
        timerThread = std::thread(&TimerPlugin::timerLoop, this);
    }
}

void TimerPlugin::stop() {
    if (running) {
        running = false;
        if (timerThread.joinable()) {
            timerThread.join();
        }
    }
}

void TimerPlugin::timerLoop() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        if (running) {
            callback();
        }
    }
}

void TimerPlugin::execute(GradeManager* grademanager_ptr) {
    while (true) {
        int choice;
        std::cout << "1. 设置时间间隔" << std::endl;
        std::cout << "2. 设置函数" << std::endl;
        std::cout << "3. 开启定时器" << std::endl;
        std::cout << "4. 关闭定时器" << std::endl;
        std::cout << "0. 返回菜单" << std::endl;
        std::cout << "输入选项： ";
        std::cout << std::endl;

        std::cin >> choice;

        std::cout << std::endl;


        switch (choice) {
            case 1: {
                std::cout << "输入时间间隔(以秒为单位)" << std::endl;
                std::cin>>interval;
                break;
            }
            case 2: {
                std::cout<<"输入函数ID"<<std::endl;
                std::cout<<"1.输出全部信息"<<std::endl;
                std::cout<<"2.输出最高分与最低分"<<std::endl;
                std::cout<<"3.输出平均分"<<std::endl;
                std::cout<<"4.自动按照科目排序"<<std::endl;
                int functionId;
                std::cin>>functionId;
                switch (functionId) {
                    case 1: {
                        callback = std::bind(&GradeManager::displayGrades, grademanager_ptr);
                        break;
                    }
                    case 2: {
                        callback = std::bind(&GradeManager::queryMaxAndMin, grademanager_ptr);
                        break;
                    }
                    case 3: {
                        callback = std::bind(&GradeManager::displayAverageScores, grademanager_ptr);
                        break;
                    }
                    case 4: {
                        std::cout<<"输入科目"<<std::endl;
                        std::cin>>grademanager_ptr->callback_sortByScores_varaible;
                        callback = std::bind(&GradeManager::callback_sortByScores, grademanager_ptr);
                        break;
                    }
                    default: {
                        std::cout<<"输入错误"<<std::endl;
                        break;
                    }
                }
                break;
            }
            case 3: {
                if(callback==nullptr){
                    std::cout<<"未设置函数"<<std::endl;
                    break;
                }
                start();
                break;
            }
            case 4: {
                stop();
                break;
            }
            case 0: {
                return;
            }
        }
    }

}
