#pragma once
#include <action_node.h>
#include <condition_node.h>

namespace BT
{

class Pick : public BT::ActionNode
{
public:
    Pick(std::string name, std::string location);
    ~Pick();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
    std::string location_;
};

class Hold : public BT::ConditionNode
{
public:
    Hold(std::string name, std::string location);
    ~Hold();
    BT::ReturnStatus Tick();
private:
   std::string name_;
   std::string location_;
};

class HandEmpty : public BT::ConditionNode
{
public:
    HandEmpty(std::string name);
    ~HandEmpty();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class Approach : public BT::ConditionNode
{
public:
    Approach(std::string name, std::string destination);
    ~Approach();
    BT::ReturnStatus Tick();
private:
   std::string name_;
   std::string destination_;
};

class Place : public BT::ActionNode
{
public:
    Place(std::string name, std::string location, std::string destination);
    ~Place();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
    std::string location_;
    std::string destination_;
};

class On : public BT::ConditionNode
{
public:
    On(std::string name, std::string location, std::string destination);
    ~On();
    BT::ReturnStatus Tick();
private:
    std::string name_;
    std::string location_;
    std::string destination_;
};

class MoveTo : public BT::ActionNode
{
public:
    MoveTo(std::string location);
    ~MoveTo();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string location_;
};

class Near : public BT::ConditionNode
{
public:
    Near(std::string name, std::string location);
    ~Near();
    BT::ReturnStatus Tick();
private:
    std::string name_;
    std::string location_;
};

class ExistPath : public BT::ConditionNode
{
public:
    ExistPath(std::string location);
    ~ExistPath();
    BT::ReturnStatus Tick();
private:
    std::string location_;
};

class Remove : public BT::ActionNode
{
public:
    Remove(std::string name, std::string location, std::string obstacle);
    ~Remove();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
    std::string location_;
    std::string obstacle_;
};

class Drop : public BT::ActionNode
{
public:
    Drop(std::string name, std::string location);
    ~Drop();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
    std::string location_;
};
}
