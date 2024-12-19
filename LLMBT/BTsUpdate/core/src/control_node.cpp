/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <control_node.h>
#include <string>
#include <vector>

BT::ControlNode::ControlNode(std::string name) : TreeNode::TreeNode(name)
{
    type_ = BT::CONTROL_NODE;
    // TODO(...) In case it is desired to set to idle remove the ReturnStatus
    // type in order to set the member variable
    // ReturnStatus child_i_status_ = BT::IDLE;  // commented out as unused
}

BT::ControlNode::~ControlNode() {}

void BT::ControlNode::AddChild(TreeNode* child)
{
//    // Checking if the child is not already present
//    for (unsigned int i=0; i<children_nodes_.size(); i++)
//    {
//        if (children_nodes_[i] == child)
//        {
//            throw BehaviorTreeException("'" + child->get_name() + "' is already a '" + get_name() + "' child.");
//        }
//    }
    children_nodes_.push_back(child);
    children_states_.push_back(BT::IDLE);
}

unsigned int BT::ControlNode::GetChildrenNumber()
{
    return children_nodes_.size();
}

void BT::ControlNode::Halt()
{
    std::cout << "Halting: " << get_name() << std::endl;
    //DEBUG_STDOUT("HALTING: "<< get_name());
    HaltChildren(0);
    set_status(BT::HALTED);
}

std::vector<BT::TreeNode*> BT::ControlNode::GetChildren()
{
    return children_nodes_;
}

void BT::ControlNode::ResetColorState()
{
    set_color_status(BT::IDLE);
    for (unsigned int i = 0; i < children_nodes_.size(); i++)
    {
        children_nodes_[i]->ResetColorState();
    }
}

void BT::ControlNode::Finalize()
{
    for (unsigned int i = 0; i < children_nodes_.size(); i++)
    {
        children_nodes_[i]->Finalize();
    }
}


void BT::ControlNode::HaltChildren(int i)
{
    for (unsigned int j=i; j < children_nodes_.size(); j++)
    {
        if (children_nodes_[j]->get_type() == BT::CONDITION_NODE)
        {
            children_nodes_[j]->ResetColorState();
        }
        else
        {
            if (children_nodes_[j]->get_status() == BT::RUNNING)
            {
                std::cout << "Sending halt to child " << children_nodes_[j]-> get_name() << std::endl;
                if(children_nodes_[j]->get_type() == BT::ACTION_NODE)
                {
                    // if it is an action, i need to halt using the halt_request 
                    children_nodes_[j]->halt_requested(true);
                    children_nodes_[j]->Halt();
                    //wait for the child j to be halted
                    do
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        //std::cout <<" Waiting fo halt of " << children_nodes_[j]-> get_name() <<  " status: " << children_nodes_[j]->get_status()  <<  std::endl;
                    }
                    while (children_nodes_[j]->get_status() != BT::HALTED  && children_nodes_[j]->get_status() != BT::IDLE );
                }
                else
                { // is a control flow node (or yarp action)
                    children_nodes_[j]->Halt();
                }
            }
            else
            {
                //std::cout << "NO NEED TO HALT XXX" << children_nodes_[j]-> get_name() << "STATUS" << children_nodes_[j]->get_status() << std::endl;
            }
        }
    }
}

int BT::ControlNode::Depth()
{
    int depMax = 0;
    int dep = 0;
    for (unsigned int i = 0; i < children_nodes_.size(); i++)
    {
        dep = (children_nodes_[i]->Depth());
        if (dep > depMax)
        {
            depMax = dep;
        }
    }
    return 1 + depMax;
}

BT::RootNode::RootNode() : ControlNode::ControlNode("root")
{

}

BT::RootNode::~RootNode()
{

}

BT::ReturnStatus BT::RootNode::Tick()
{
    // gets the number of children. The number could change if, at runtime, one edits the tree.
    N_of_children_ = children_nodes_.size();

    if (N_of_children_ > 1)
    {
        std::cout << "root can have at most one child" << std::endl;
        exit(1);
    }

    if (N_of_children_  == 0)
    {
        std::cout << "root has no child" << std::endl;
        exit(1);
    }

    if (children_nodes_[0]->get_type() == BT::ACTION_NODE || children_nodes_[0]->get_type() == BT::YARP_ACTION_NODE)
    {
        // 1) If the child i is an action, read its state.
        child_i_status_ = children_nodes_[0]->get_status();

        if (child_i_status_ == BT::IDLE || child_i_status_ == BT::HALTED)
        {
            // 1.1) If the action status is not running, the sequence node sends a tick to it.
            children_nodes_[0]->tick_engine.Tick();

            // waits for the tick to arrive to the child
            do
            {
                child_i_status_ = children_nodes_[0]->get_status();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            while (child_i_status_ != BT::RUNNING && child_i_status_ != BT::SUCCESS
                   && child_i_status_ != BT::FAILURE);
        }
    }
    else
    {
        // 2) if it's not an action:
        // Send the tick and wait for the response;
        child_i_status_ = children_nodes_[0]->Tick();
        children_nodes_[0]->set_status(child_i_status_);
    }

    if (child_i_status_ == BT::FAILURE)
    {
        if(children_nodes_[0]->get_type() == BT::CONDITION_NODE)//|| children_nodes_[i]->get_type() == BT::ACTION_NODE
        {
            last_failed_Node = children_nodes_[0]->get_name();
        }
        else
        {
            last_failed_Node = children_nodes_[0]->last_failed_Node;
        }
    }
    return child_i_status_;
}

int BT::RootNode::DrawType()
{
    return BT::ROOT;
}

