#pragma once

#include "../PluginInterface.h"
#include "../../GradeManager/GradeManager.h"
#include <string>

class DefaultDataPlugin : public PluginInterface {
public:
    void getDfaultData(GradeManager*) const ;
    void execute(GradeManager*) override;
};

extern "C" std::unique_ptr<PluginInterface> create_Plugin() {
    return std::make_unique<DefaultDataPlugin>();
}