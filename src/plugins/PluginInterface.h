#pragma once

#include <memory>
class PluginInterface {
public:
    virtual ~PluginInterface() {}

    virtual void execute() = 0;
};
