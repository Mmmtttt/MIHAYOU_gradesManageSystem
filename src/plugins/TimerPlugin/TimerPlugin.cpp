#include "TimerPlugin.h"

TimerPlugin::TimerPlugin(int intervalInSeconds, std::function<void()> callback)
    : interval(intervalInSeconds), callback(callback), running(false) {}

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

void TimerPlugin::execute(){
    std::cout << "执行指定功能" << std::endl;
}