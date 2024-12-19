#pragma once

#include "BehaviorTreeNodeModel.h"

class Search : public BehaviorTreeNodeModel
{
public:
    Search():
        BehaviorTreeNodeModel("Search", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::SEARCH;
    }
    virtual ~Search() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Search ); }

    virtual QString name() const override { return QString("Search"); }
};

class IsFind : public BehaviorTreeNodeModel
{
public:
    IsFind():
        BehaviorTreeNodeModel("IsFind", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISFIND;
    }
    virtual ~IsFind() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsFind ); }

    virtual QString name() const override { return QString("IsFind"); }
};

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

class IsObjectOnHand : public BehaviorTreeNodeModel
{
public:
    IsObjectOnHand():
        BehaviorTreeNodeModel("IsObjectOnHand", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISOBJECTONHAND;
    }
    virtual ~IsObjectOnHand() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsObjectOnHand ); }

    virtual QString name() const override { return QString("IsObjectOnHand"); }
};

class IsHandEmpty : public BehaviorTreeNodeModel
{
public:
    IsHandEmpty():
        BehaviorTreeNodeModel("IsHandEmpty", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISHANDEMPTY;
    }
    virtual ~IsHandEmpty() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsHandEmpty ); }

    virtual QString name() const override { return QString("IsHandEmpty"); }
};

class IsPathToObject : public BehaviorTreeNodeModel
{
public:
    IsPathToObject():
        BehaviorTreeNodeModel("IsPathToObject", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISPATHTOOBJECT;
    }
    virtual ~IsPathToObject() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsPathToObject ); }

    virtual QString name() const override { return QString("IsPathToObject"); }
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

class IsObjectOnDestination : public BehaviorTreeNodeModel
{
public:
    IsObjectOnDestination():
        BehaviorTreeNodeModel("IsObjectOnDestination", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISOBJECTONDESTINATION;
    }
    virtual ~IsObjectOnDestination() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsObjectOnDestination ); }

    virtual QString name() const override { return QString("IsObjectOnDestination"); }
};

class IsPathToDestination : public BehaviorTreeNodeModel
{
public:
    IsPathToDestination():
        BehaviorTreeNodeModel("IsPathToDestination", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISPATHTODESTINATION;
    }
    virtual ~IsPathToDestination() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsPathToDestination ); }

    virtual QString name() const override { return QString("IsPathToDestination"); }
};