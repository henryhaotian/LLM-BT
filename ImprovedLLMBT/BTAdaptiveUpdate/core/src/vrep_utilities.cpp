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

std::string Move_Signal;
std::string Move_Value = " ";

std::string Remove_Signal;
std::string Remove_Value = " ";

std::string Drop_Signal;
std::string Drop_Value = " ";

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
        Move_Signal = "move_signal";
        Remove_Signal = "remove_signal";
        Drop_Signal = "drop_signal";

        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
        simxSetStringSignal(clientID, Move_Signal.c_str(), (simxUChar*)Move_Value.c_str(), Move_Value.size(), mode);
        simxSetStringSignal(clientID, Remove_Signal.c_str(), (simxUChar*)Remove_Value.c_str(), Remove_Value.size(), mode);
        simxSetStringSignal(clientID, Drop_Signal.c_str(), (simxUChar*)Drop_Value.c_str(), Drop_Value.size(), mode);
    }

    std::string GetCurrentObstacle(std::string name)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"GetObstacle",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        return output_string;
    }

    void Pick(std::string name, std::string location)
    {
        Pick_Value = name;
        simxSetStringSignal(clientID, Pick_Signal.c_str(), (simxUChar*)Pick_Value.c_str(), Pick_Value.size(), mode);
    }

    bool Hold(std::string name, std::string location)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = name.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"IsObjectOnHand",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
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
    
    bool HandEmpty(std::string name)
    {
        int output_string_num;
        char* output_string;
        simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"IsHandEmpty",0,NULL,0,NULL,0,NULL,0,NULL,
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

    bool Approach(std::string name,std::string destination)
    {
        int input_string_num = 2;
        int output_string_num;
        const char* input_string;
        char* output_string;
        std::string a = '\0' + destination;
        std::string b = name+a;
        input_string = b.c_str();
        int result=simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"IsCouldApproachObject",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
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

    void Place(std::string name, std::string location, std::string destination)
    {
        Place_Value = destination;
        simxSetStringSignal(clientID, Place_Signal.c_str(), (simxUChar*)Place_Value.c_str(), Place_Value.size(), mode);
    }

    bool On(std::string name, std::string location, std::string destination)
    {
        int input_string_num = 2;
        int output_string_num;
        const char* input_string;
        char* output_string;
        std::string a = '\0' + destination;
        std::string b = name+a;
        input_string = b.c_str();
        int result=simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"IsObjectOnGoal",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
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

    void MoveTo(std::string location)
    {
        Move_Value = location;
        simxSetStringSignal(clientID, Move_Signal.c_str(), (simxUChar*)Move_Value.c_str(), Move_Value.size(), mode);
    }

    bool Near(std::string name, std::string location)
    {
        int input_string_num = 1;
        int output_string_num;
        const char* input_string = location.c_str();
        char* output_string;
        int result=simxCallScriptFunction(clientID,"Omnirob",sim_scripttype_childscript,"IsRobotNearLocation",0,NULL,0,NULL,input_string_num,input_string,0,NULL,
        NULL,NULL,NULL,NULL,&output_string_num,&output_string,NULL,NULL,simx_opmode_blocking);
        std::string res = output_string;
        if (res == "true")
        {
            sleep(1);
            return true;
        }
        else if (res == "false")
        {
            return false;
        }
    }

    bool ExistPath(std::string location)
    {
        sleep(1);
        return true;
    }

    void Remove(std::string name, std::string location, std::string obstacle)
    {
        Remove_Value = name;
        simxSetStringSignal(clientID, Remove_Signal.c_str(), (simxUChar*)Remove_Value.c_str(), Remove_Value.size(), mode);
    }

    void Drop(std::string name, std::string location)
    {
        Drop_Value = name;
        simxSetStringSignal(clientID, Drop_Signal.c_str(), (simxUChar*)Drop_Value.c_str(), Drop_Value.size(), mode);
    }
}
