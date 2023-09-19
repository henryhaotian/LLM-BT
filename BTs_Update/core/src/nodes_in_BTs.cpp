#include <iostream>
//#include <behavior_tree.h>
#include <nodes_in_BTs.h>
#include <vrep_utilities.h>

BT::Search::Search(std::string name) : ActionNode::ActionNode("Search "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::Search::Tick()
{
    std::cout << "Execute: Search " <<  name_ << std::endl;
    vrep_utilities::Search(name_);
    return BT::RUNNING;
}

void BT::Search::Halt()
{
    std::cout << "Halt: Search " << name_ << std::endl;
    set_status(BT::HALTED);
}

BT::IsFind::IsFind(std::string name) : ConditionNode::ConditionNode("IsFind "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsFind::Tick()
{
    std::cout << "Check: IsFind " << name_ << std::endl;
    if (vrep_utilities::IsFind(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::Pick::Pick(std::string name) : ActionNode::ActionNode("Pick "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::Pick::Tick()
{
    std::cout << "Execute: Pick " <<  name_ << std::endl;
    vrep_utilities::Pick(name_);
    return BT::RUNNING;
}

void BT::Pick::Halt()
{
    std::cout << "Halt: Pick " << name_ << std::endl;
    set_status(BT::HALTED);
}

BT::IsObjectOnHand::IsObjectOnHand(std::string name) : ConditionNode::ConditionNode("IsObjectOnHand "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsObjectOnHand::Tick()
{
    std::cout << "Check: IsObjectOnHand " << name_ << std::endl;
    if (vrep_utilities::IsObjectOnHand(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsHandEmpty::IsHandEmpty(std::string name) : ConditionNode::ConditionNode("IsHandEmpty "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsHandEmpty::Tick()
{
    std::cout << "Check: IsHandEmpty " << name_ << std::endl;
    if (vrep_utilities::IsHandEmpty(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsPathToObject::IsPathToObject(std::string name) : ConditionNode::ConditionNode("IsPathToObject "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsPathToObject::Tick()
{
    std::cout << "Check: IsPathToObject " << name_ << std::endl;
    if (vrep_utilities::IsPathToObject(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }

}

BT::Place::Place(std::string name) : ActionNode::ActionNode("Place "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::Place::Tick()
{
    std::cout << "Execute: Place " << name_ << std::endl;
    vrep_utilities::Place(name_);
    return BT::RUNNING;
}

void BT::Place::Halt()
{
std::cout << "Halt: Place " << name_ << std::endl;
set_status(BT::HALTED);
}

BT::IsObjectOnDestination::IsObjectOnDestination(std::string name,std::string goal) : ConditionNode::ConditionNode("IsObjectOnDestination "+name+","+goal)
{
    name_ = name;
    goal_ = goal;
}

BT::ReturnStatus BT::IsObjectOnDestination::Tick()
{
    std::cout << "Check: IsObjectOnDestination " << name_ << "," << goal_ << std::endl;
    if (vrep_utilities::IsObjectOnDestination(name_,goal_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsPathToDestination::IsPathToDestination(std::string goal) : ConditionNode::ConditionNode("IsPathToDestination "+goal)
{
    goal_ = goal;
}

BT::ReturnStatus BT::IsPathToDestination::Tick()
{
    std::cout << "Check: IsPathToDestination " << goal_ << std::endl;
    if (vrep_utilities::IsPathToDestination(goal_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}
