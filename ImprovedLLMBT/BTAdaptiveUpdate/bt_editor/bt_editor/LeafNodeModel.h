#pragma once

#include "BehaviorTreeNodeModel.h"

class Pick : public BehaviorTreeNodeModel
{
public:
    Pick():
        BehaviorTreeNodeModel("Pick", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::PICK;
    }
    virtual ~Pick() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Pick ); }

    virtual QString name() const override { return QString("Pick"); }
};

class Hold : public BehaviorTreeNodeModel
{
public:
    Hold():
        BehaviorTreeNodeModel("Hold", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::HOLD;
    }
    virtual ~Hold() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Hold ); }

    virtual QString name() const override { return QString("Hold"); }
};

class HandEmpty : public BehaviorTreeNodeModel
{
public:
    HandEmpty():
        BehaviorTreeNodeModel("HandEmpty", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::HANDEMPTY;
    }
    virtual ~HandEmpty() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new HandEmpty ); }

    virtual QString name() const override { return QString("HandEmpty"); }
};

class Approach : public BehaviorTreeNodeModel
{
public:
    Approach():
        BehaviorTreeNodeModel("Approach", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::APPROACH;
    }
    virtual ~Approach() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Approach ); }

    virtual QString name() const override { return QString("Approach"); }
};

class Place : public BehaviorTreeNodeModel
{
public:
    Place():
        BehaviorTreeNodeModel("Place", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::PLACE;
    }
    virtual ~Place() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Place ); }

    virtual QString name() const override { return QString("Place"); }
};

class On : public BehaviorTreeNodeModel
{
public:
    On():
        BehaviorTreeNodeModel("On", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ON;
    }
    virtual ~On() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new On ); }

    virtual QString name() const override { return QString("On"); }
};

class MoveTo : public BehaviorTreeNodeModel
{
public:
    MoveTo():
        BehaviorTreeNodeModel("MoveTo", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::MOVETO;
    }
    virtual ~MoveTo() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new MoveTo ); }

    virtual QString name() const override { return QString("MoveTo"); }
};

class Near : public BehaviorTreeNodeModel
{
public:
    Near():
        BehaviorTreeNodeModel("Near", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::NEAR;
    }
    virtual ~Near() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Near ); }

    virtual QString name() const override { return QString("Near"); }
};

class ExistPath : public BehaviorTreeNodeModel
{
public:
    ExistPath():
        BehaviorTreeNodeModel("ExistPath", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::EXISTPATH;
    }
    virtual ~ExistPath() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new ExistPath ); }

    virtual QString name() const override { return QString("ExistPath"); }
};

class Remove : public BehaviorTreeNodeModel
{
public:
    Remove():
        BehaviorTreeNodeModel("Remove", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::REMOVE;
    }
    virtual ~Remove() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Remove ); }

    virtual QString name() const override { return QString("Remove"); }
};

class Drop : public BehaviorTreeNodeModel
{
public:
    Drop():
        BehaviorTreeNodeModel("Drop", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::DROP;
    }
    virtual ~Drop() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Drop ); }

    virtual QString name() const override { return QString("Drop"); }
};