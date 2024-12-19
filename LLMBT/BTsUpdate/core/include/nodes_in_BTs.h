#pragma once
#include <action_node.h>
#include <condition_node.h>

namespace BT
{
class Search : public BT::ActionNode
{
public:
    Search(std::string name);
    ~Search();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

class IsFind : public BT::ConditionNode
{
public:
    IsFind(std::string name);
    ~IsFind();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class Pick : public BT::ActionNode
{
public:
    Pick(std::string name);
    ~Pick();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

class IsObjectOnHand : public BT::ConditionNode
{
public:
    IsObjectOnHand(std::string name);
    ~IsObjectOnHand();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class IsHandEmpty : public BT::ConditionNode
{
public:
    IsHandEmpty(std::string name);
    ~IsHandEmpty();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class IsPathToObject : public BT::ConditionNode
{
public:
    IsPathToObject(std::string name);
    ~IsPathToObject();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class Place : public BT::ActionNode
{
public:
    Place(std::string name);
    ~Place();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

class IsObjectOnDestination : public BT::ConditionNode
{
public:
    IsObjectOnDestination(std::string name, std::string goal);
    ~IsObjectOnDestination();
    BT::ReturnStatus Tick();
private:
   std::string name_;
   std::string goal_;
};

class IsPathToDestination : public BT::ConditionNode
{
public:
    IsPathToDestination(std::string goal);
    ~IsPathToDestination();
    BT::ReturnStatus Tick();
private:
   std::string goal_;
};

}
