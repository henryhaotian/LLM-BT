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
    std::vector<std::string> getSuccessNodes();
    void clearSuccessNodes();

    void Search(std::string name);
    bool IsFind(std::string name);

    void Pick(std::string name);
    bool IsObjectOnHand(std::string name);
    bool IsHandEmpty(std::string name);
    bool IsPathToObject(std::string name);

    void Place(std::string goal);
    bool IsObjectOnDestination(std::string name, std::string goal);
    bool IsPathToDestination(std::string goal);

}

#endif // VREP_UTILITIES_H
