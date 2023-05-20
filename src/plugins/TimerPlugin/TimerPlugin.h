#pragma once

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include "../PluginInterface.h"
#include "../../GradeManager/GradeManager.h"

class TimerPlugin : public PluginInterface{
public:
    TimerPlugin() = default;
    TimerPlugin(int intervalInSeconds, std::function<void()> callback);
    ~TimerPlugin(){
        stop();
    }

    void start();
    void stop();

private:
    int interval;
    std::function<void()> callback;
    std::thread timerThread;
    bool running;

    void timerLoop();
    void execute(GradeManager*) override;
};

extern "C" std::unique_ptr<PluginInterface> create_Plugin() {
    return std::make_unique<TimerPlugin>();
}
