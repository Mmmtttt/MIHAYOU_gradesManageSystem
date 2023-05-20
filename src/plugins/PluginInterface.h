#pragma once

#include <memory>
#include "../GradeManager/GradeManager.h"

class PluginInterface {
public:
    virtual ~PluginInterface() {}

    virtual void execute(GradeManager*) = 0;
};
