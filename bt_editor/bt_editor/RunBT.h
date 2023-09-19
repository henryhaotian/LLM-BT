#ifndef RUNBT_H
#define RUNBT_H
#include <node_editor/NodeData>
#include <node_editor/FlowScene>
#include <QtXml>
#include <QString>
#include <QStringList>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <QThread>
#include <vrep_utilities.h>
#include "utils.h"
#include <node_editor/Node>
#include <QDebug>
#include <node_editor/Node>
#include <iostream>
#include <fstream>
#include "RootNodeModel.h"
#include "BehaviorTreeNodeModel.h"
#include <parallel_node.h>
#include <fallback_node.h>
#include <sequence_node.h>
#include <action_node.h>
#include <condition_node.h>
#include <nodes_in_BTs.h>
#include <vector>

using namespace std;

class RunBT: public QThread
{
    Q_OBJECT
public:
    RunBT();

    ~RunBT();

    void GetScene(QtNodes::FlowScene *scene_);

    void GetXMLPath(QString fileName_);

    bool UpdateTree(QString fail_node);

    QDomElement ExpandTree(QString node_name, QString node_attribute, QDomDocument& doc);

    bool ReadTree(QDomDocument &doc);

    bool WriteTree(QDomDocument doc);

    void LocateNode(QString node_name, QString node_attribute, const QDomNode &node, QDomNode &fail_node);

signals:
    void ReExecute();
protected:
    void run();
private:
    QtNodes::FlowScene *scene;
    QString fileName;
    bool first_readtree;
    int iteration_count;
    int max_node_num;
};

#endif // RUNBT_H
