#pragma once

#include "plugins/plugininterface.h"
#include "../../GradeManager/GradeManager.h"
#include <string>

class DefaultDataPlugin : public PluginInterface {
public:
    //std::string getPluginName() const override;
    void execute() override;
};

extern "C" std::unique_ptr<PluginInterface> create_Plugin() {
    return std::make_unique<DefaultDataPlugin>();
}