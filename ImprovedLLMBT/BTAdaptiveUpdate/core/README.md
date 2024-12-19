
====
A behavior tree library in `YARP`.




DEPENDENCIES
------------

Regarding visualization purposes:
* [OpenGL](https://www.opengl.org/)
* [Glut](https://www.opengl.org/resources/libraries/glut/)
* [YARP](https://www.yarp.it/)

Regarding tests:
* [GTests](https://github.com/google/googletest)

BT NODES SUPPORT
----------------
**Fallback:** Fallback nodes are used to find and execute the first child that does not fail. A Selector node will return immediately with a status code of success or running when one of its children returns success or running. The children are ticked in order of importance, from `left` to `right`.

**Sequence:** Sequence nodes are used to find and execute the first child that has not yet succeeded. A sequence node will return immediately with a status code of `failure` or `running` when one of its children returns failure or running. The children are ticked in order, from `left` to `right`.

**Parallel:** The parallel node ticks its children in parallel and returns success if `M ≤ N` children return success, it returns failure if `N − M + 1` children return failure, and it returns running otherwise.

**Decorator:** The decorator node manipulates the return status of its child according to the policy defined by the user (e.g. it inverts the success/failure status of the child). In this library the decorators implemented are the two common ones: *Decorator Retry* which retries the execution of a node if this fails; and *Decorator Negation* That inverts the Success/Failure outcome.

**Action:** An Action node performs an action, and returns Success if the action is completed, Failure if it can not be completed and Running if completion is under way.

**Condition:** A Condition node determines if a desired condition `c` has been met. Conditions are technically a subset of the Actions, but are given a separate category and graphical symbol to improve readability of the BT and emphasize the fact that they never return running and do not change any internal states/variables of the BT.

A user manual is available in the project folder ([BTppUserManual.pdf](https://github.com/miccol/Behavior-Tree/blob/master/BTppUserManual.pdf)).

SETUP
-----------

The first step to use BT++ is to retrieve its source code. You can either download it 
here (https://github.com/miccol/Behavior-Tree) or clone the repository:

`$ cd /path/to/folder` <br/>
`$ git clone https://github.com/miccol/Behavior−Tree.git`

Once you have the repository, compile the library:

`$ cd /path/to/folder/` <br/>
`$ mkdir ./build` <br/>
`$ cd build` <br/>
`$ cmake ..` <br/>
`$ make` <br/>


CREATE YOUR OWN ACTION NODE
------
1) Implement your action node class extending the abstract class `BT::ActionNode`.
2) Implement the method `BT::ReturnStatus Tick()` with the code you want to execute while the action is running. Use the method `is_halted()` to check if the action has been prempted. When the execution of your action finished, return `BT::SUCCESS` or `BT::FAILURE` accordingly.  
3) Implement the method `void Halt()` with the code you want to execute when the action gets preempted (halted).
See the file `src/example.cpp` for an example.

CREATE YOUR OWN CONDITION NODE
------
1) Implement your condition node class extending the abstract class `BT::ConditionNode`.
2) Implement the method `BT::ReturnStatus Tick()` with the code you want to execute to check the condition. Return `BT::SUCCESS` or `BT::FAILURE` accordingly.  
See the file `src/example.cpp` for an example.

### Set up an Behavior Tree's action in YARP
The file templates/yarp_bt_action_template.cpp is a template on how the your YARP BT action should look like, it performs and action (it is an action n in the Behavior Tree).
Your action is the Server and does stuff. The Behavior Tree is the Client and tells to all the Server which ones have to start (TICK) and which have to stop (HALT).

in your module you should implement two functions: bool Exec() and void Halt()


In the function bool Exec() you must write the code to be executed when the module needs to be run. The function it must return true if the execution of the action has succeeded and false if it has failed.
To allow preemption to your action, it is preferable to check whenever possible if the action has been halted checking the function is_halted().

For example:



    bool Exec()
    {
        if (!is_halted())
        {
            std::cout << "Doing Something" << std::endl;
        }
        return true;
    }


In the function Halt() you must write the code to be executed when the module need to be stopped (e.g. when stopping a walking module we would like to have to robot stop in a home position).
For Example:


    void Halt()
    {
            std::cout << "Halting the Action" << std::endl;
    }






Then set a name for your module. The name has the be unique. It will be used bt the behavior tree to recognize it. For example if you created a class called MyBTModule

     MyBTModule* action_module = new MyBTModule("/your_bt_action_name");


The file src/walking_module.cpp gives an example of a BT action node in YARP.

### Set up an Behavior Tree's condition in YARP
The procedure is similar to the one for the action node, with the only difference that you don't need to implement the function Halt().

The file templates/yarp_bt_condition_template.cpp gives an example of a BT conditon node in YARP.

    

### Test your YARP Action or Condition

You can also test if your YARP Module (Action or Condition) works properly without running the BT. 

in one terminal run your module:

     cd build
     ./your_module

and in another terminal run the progrem "test_your_module" specifing the port of your module.

     cd build
     ./test_your_module port_name

Follow the instruction in the program
Press: 1 to start the execution; 2 to halt the execution and 3 to terminate the program.




LICENSE
-------
The MIT License (MIT)

Copyright (c) 2017 Michele Colledanchise

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
