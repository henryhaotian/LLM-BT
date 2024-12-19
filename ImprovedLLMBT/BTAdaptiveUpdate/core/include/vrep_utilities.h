#ifndef VREP_UTILITIES_H
#define VREP_UTILITIES_H

#include <iostream>
#include <vector>

extern "C" {
    #include "extApi.h"
/*	#include "extApiCustom.h" if you wanna use custom remote API functions! */
}

enum
{
    bt_result_success = 1,
    bt_result_running = 0,
    bt_result_failure = -1,
    bt_result_idle = 2
};

namespace vrep_utilities
{
    void init();
    void startSimulation();
    void stopSimulation();

    std::string GetCurrentObstacle(std::string name);
    
    void Pick(std::string name,std::string location);
    bool Hold(std::string name,std::string location);
    bool HandEmpty(std::string name);
    bool Approach(std::string name, std::string destination);

    void Place(std::string name, std::string location, std::string destination);
    bool On(std::string name, std::string location, std::string destination);

    void MoveTo(std::string location);
    bool Near(std::string name, std::string location);

    bool ExistPath(std::string location);
    void Remove(std::string name, std::string location, std::string obstacle);
    void Drop(std::string name, std::string location);
}

#endif // VREP_UTILITIES_H
