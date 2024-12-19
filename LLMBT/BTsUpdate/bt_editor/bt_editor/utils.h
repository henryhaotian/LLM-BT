#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <node_editor/NodeData>
#include <node_editor/FlowScene>
#include <QDomDocument>
#include <QFile>
#include <QtXml>
#include <QString>
#include <QStringList>

#include "BehaviorTreeNodeModel.h"
#include <parallel_node.h>
#include <fallback_node.h>
#include <sequence_node.h>
#include <action_node.h>
#include <condition_node.h>
#include <nodes_in_BTs.h>

std::vector<QtNodes::Node*> findRoots(const QtNodes::FlowScene &scene);

std::vector<QtNodes::Node*> getChildren(const QtNodes::FlowScene &scene,
                                        const QtNodes::Node &parent_node);

void NodeReorder(QtNodes::FlowScene& scene);

void NodeReorderRecursive(QtNodes::FlowScene &scene,QtNodes::Node& node,QPointF cursor,int level,std::map<int, 
std::vector<QtNodes::Node*>>& nodes_by_level);

void SubtreeReorder(QtNodes::FlowScene &scene, QtNodes::Node &root_node);

void SubtreeReorderRecursive(QtNodes::FlowScene &scene,QtNodes::Node& node,QtNodes::Node& root_node,QPointF cursor,
int level,std::map<int, std::vector<QtNodes::Node*>>& nodes_by_level);

void calculateForces(QtNodes::FlowScene *scene);

void updateBTColors(QtNodes::FlowScene* scene, QtNodes::Node* node, std::string* return_string);

void setMode(int mode);

int getMode();

bool is_BT_valid(QtNodes::FlowScene* scene);

BT::TreeNode *getBTObject(QtNodes::FlowScene &scene, QtNodes::Node &node);

int getNodeNum();

#endif // NODE_UTILS_H
