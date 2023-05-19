#include "DefaultDataPlugin.h"

#include <iostream>

// std::string DefaultDataPlugin::getPluginName() const {
//     return "DefaultDataPlugin";
// }

extern "C" void DefaultDataPlugin::execute() {
    std::cout << "查找缺省数据(插件功能)" << std::endl;
    
}
