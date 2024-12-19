#include "vrep_utilities.h"
#include <chrono>
#include <thread>
#include <complex>
#include <mutex>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
    #include "extApi.h"
   // #include "extApiCustom.h" // if you wanna use custom remote API functions!
}
//success node of IsObjectOnGoal
std::vector<std::string> success_nodes;

simxInt clientID, mode = simx_opmode_oneshot_wait;

std::string Pick_Signal;
std::string Pick_Value = " ";

std::string Place_Signal;
std::string Place_Value = " ";

namespace vrep_utilities
{

    void startSimulation()
    {
       simxStartSimulation(clientID, 0);
    }
    void stopSimulation()
    {
        simxStopSimulation(clientID, 0);
    }

    void init()
    {
        clientID = simxStart((simxChar*)"127.0.0.1",19997,true,false,2000,5);

        Pick_Signal = "pick_signal";
        Place_Signal = "place_signal";

        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
    }

    std::vector<std::string> getSuccessNodes()
    {
        return success_nodes;
    }

    void clearSuccessNodes()
    {
        success_nodes.clear();
    }

    void Search(std::string name)
    {

    }

    bool IsFind(std::string name)
    {
        return true;
    }

    void Pick(std::string name)
    {
        Pick_Value = name;
        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
    }

    bool IsObjectOnHand(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsObjectOnHand",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }
    
    bool IsHandEmpty(std::string name)
    {
        int output_string_num;
        char* output_string;
        simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsHandEmpty",0,NULL,0,NULL,0,NULL,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    bool IsPathToObject(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsCouldApproachObject",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    bool IsPathToDestination(std::string goal)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = goal.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsCouldApproachGoal",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    void Place(std::string goal)
    {
        Place_Value = goal;
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
    }

    bool IsObjectOnDestination(std::string name, std::string goal)
    {
        int input_string_num = 2;
        int output_string_num;
        const char* input_string;
        char* output_string;
        std::string a = '\0' + goal;
        std::string b = name+a;
        input_string = b.c_str();
        int result=simxCallScriptFunction(clientID,"UR5",sim_scripttype_childscript,"IsObjectOnGoal",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

}
