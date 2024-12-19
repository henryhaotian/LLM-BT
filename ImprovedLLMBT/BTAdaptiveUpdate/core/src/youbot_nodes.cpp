#include <iostream>
//#include <behavior_tree.h>
#include <youbot_nodes.h>
#include <vrep_utilities.h>

BT::Pick::Pick(std::string name, std::string location) : ActionNode::ActionNode("Pick "+name+","+location)
{
    name_ = name;
    location_ = location;
}

BT::ReturnStatus BT::Pick::Tick()
{
    std::cout << "Execute: Pick " <<  name_ << "," << location_ << std::endl;
    vrep_utilities::Pick(name_,location_);
    return BT::RUNNING;
}

void BT::Pick::Halt()
{
    std::cout << "Halt: Pick " << std::endl;
    set_status(BT::HALTED);
}

BT::Hold::Hold(std::string name, std::string location) : ConditionNode::ConditionNode("Hold "+name+","+location)
{
    name_ = name;
    location_ = location;
}

BT::ReturnStatus BT::Hold::Tick()
{
    std::cout << "Check: Hold " << name_ << "," << location_ << std::endl;
    if (vrep_utilities::Hold(name_,location_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::HandEmpty::HandEmpty(std::string name) : ConditionNode::ConditionNode("HandEmpty "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::HandEmpty::Tick()
{
    std::cout << "Check: HandEmpty " << name_ << std::endl;
    if (vrep_utilities::HandEmpty(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::Approach::Approach(std::string name,std::string destination) : ConditionNode::ConditionNode("Approach "+name+","+destination)
{
    name_ = name;
    destination_ = destination;
}

BT::ReturnStatus BT::Approach::Tick()
{
    std::cout << "Check: Approach " << name_ << "," << destination_ << std::endl;
    if (vrep_utilities::Approach(name_,destination_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::Place::Place(std::string name, std::string location, std::string destination) : ActionNode::ActionNode("Place "+name+","+location+","+destination)
{
    name_ = name;
    location_ = location;
    destination_ = destination;
}

BT::ReturnStatus BT::Place::Tick()
{
    std::cout << "Execute: Place " << name_ << "," << destination_ << std::endl;
    vrep_utilities::Place(name_, location_, destination_);
    return BT::RUNNING;
}

void BT::Place::Halt()
{
    std::cout << "Halt: Place " << std::endl;
    set_status(BT::HALTED);
}

BT::On::On(std::string name, std::string location, std::string destination) : ConditionNode::ConditionNode("On "+name+","+location+","+destination)
{
    name_ = name;
    location_ = location;
    destination_ = destination;
}

BT::ReturnStatus BT::On::Tick()
{
    std::cout << "Check: On " << name_ << "," << location_ << "," << destination_ << std::endl;
    if (vrep_utilities::On(name_,location_,destination_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::MoveTo::MoveTo(std::string location) : ActionNode::ActionNode("MoveTo "+location)
{
    location_ = location;
}

BT::ReturnStatus BT::MoveTo::Tick()
{
    std::cout << "Execute: MoveTo " <<  location_ << std::endl;
    vrep_utilities::MoveTo(location_);
    return BT::RUNNING;
}

void BT::MoveTo::Halt()
{
    std::cout << "Halt: MoveTo " << std::endl;
    set_status(BT::HALTED);
}

BT::Near::Near(std::string name,std::string location) : ConditionNode::ConditionNode("Near "+name+","+location)
{
    name_ = name;    
    location_ = location;
}

BT::ReturnStatus BT::Near::Tick()
{
    std::cout << "Check: Near " << location_ << std::endl;
    if (vrep_utilities::Near(name_,location_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::ExistPath::ExistPath(std::string location) : ConditionNode::ConditionNode("ExistPath "+location)
{
    location_ = location;
}

BT::ReturnStatus BT::ExistPath::Tick()
{
    std::cout << "Check: ExistPath " << location_ << std::endl;
    if (vrep_utilities::ExistPath(location_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::Remove::Remove(std::string name, std::string location, std::string obstacle) : ActionNode::ActionNode("Remove "+name+","+location+","+obstacle)
{
    name_ = name;
    location_ = location;
    obstacle_ = obstacle;
}

BT::ReturnStatus BT::Remove::Tick()
{
    std::cout << "Execute: Remove " << name_ << std::endl;
    vrep_utilities::Remove(name_,location_,obstacle_);
    return BT::RUNNING;
}

void BT::Remove::Halt()
{
    std::cout << "Halt: Remove " << std::endl;
    set_status(BT::HALTED);
}

BT::Drop::Drop(std::string name, std::string location) : ActionNode::ActionNode("Drop "+name+","+location)
{
    name_ = name;
    location_ = location;
}

BT::ReturnStatus BT::Drop::Tick()
{
    std::cout << "Execute: Drop " <<  name_ << std::endl;
    vrep_utilities::Drop(name_,location_);
    return BT::RUNNING;
}

void BT::Drop::Halt()
{
    std::cout << "Halt: Drop " << std::endl;
    set_status(BT::HALTED);
}