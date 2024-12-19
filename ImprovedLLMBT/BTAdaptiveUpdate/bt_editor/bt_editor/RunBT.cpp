#include "RunBT.h"
extern "C" {
    #include "extApi.h"
}

RunBT::RunBT()
{
    first_readtree = true;
    vrep_utilities::init();
    iteration_count = 0;
    max_node_num = 0;
    timer_start = true;
    timer_end = true;
    BT_duration= 0;
    expansion_duration= 0;
    vrep_utilities::startSimulation();
}

RunBT::~RunBT()
{

}

void RunBT::GetScene(QtNodes::FlowScene *scene_)
{
    scene = scene_;
}

void RunBT::GetXMLPath(QString fileName_)
{
    fileName = fileName_;
}

void RunBT::run()
{
    if (timer_start)
    {
        time_for_BT.start();
        timer_start = false;
    }

    QtNodes::Node* root;
    std::vector<QtNodes::Node*> roots = findRoots(*scene);

    if (roots.empty())
    {
        std::cout << "No Root found" << std::endl;
        return;
    }

    root= roots.at(0);

    BT::TreeNode* bt_root = getBTObject(*scene, *root);

    while (getMode() == 1)
    {
        std::cout << std::endl;
        std::cout << "Ticking the root node !" << std::endl;

        // Ticking the root node
        BT::ReturnStatus result = bt_root->Tick();

        scene->update();

        for (auto &it : scene->nodes())
        {
            QtNodes::Node *node = it.second.get();
            node->nodeGraphicsObject().update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        std::cout << "Iteration : " << iteration_count << std::endl;
        int node_num = getNodeNum();
        std::cout << "BT node num: " << node_num << std::endl;
        if (max_node_num < node_num)
        {
            max_node_num = node_num;
        }
        std::cout << "Max BT node num: " << max_node_num << std::endl;

        if (result == BT::FAILURE)
        {
            std::cout << "BT Return Failure, Failed Node: " << bt_root->last_failed_Node << std::endl;
            std::cout << "Halting the BT" << std::endl;
            bt_root->Halt();
            if(!UpdateTree(QString::fromStdString(bt_root->last_failed_Node)))
            {
                std::cout << "Update BT Failed" << std::endl;
                return;
            }
            else
            {
                std::cout << "Update BT Success" << std::endl;
                iteration_count++;
                emit ReExecute();
                return;
            }
        }
        if (result == BT::SUCCESS)
        {
            if (timer_end)
            {
                BT_duration = time_for_BT.elapsed();
                timer_end = false;
            }
            qDebug() << "Time: " << BT_duration << "ms\n";
            emit ReExecute();
            return;
        }
    }
    std::cout << "Halting the BT" << std::endl;
    bt_root->Halt();
}

bool RunBT::UpdateTree(QString fail_node)
{
    time_for_expansion.start();

    QStringList node_param = fail_node.split(" ");

    QDomDocument doc;
    if(!ReadTree(doc))
    {
        return false;
    }
    QDomElement root = doc.documentElement();

    if( root.tagName() != "root" )
    {
        qDebug() << "Expecting the node <root> in the XML \n";
        return false;
    }

    QDomElement behaviortree_root = root.firstChildElement("BehaviorTree");
    QDomNode node = behaviortree_root.firstChild();

    //get all local goals
    localgoals = node.childNodes();

    QDomNode failed_node;
    LocateNode(node_param[0],node_param[1],node,failed_node);

    QDomElement new_subtree = ExpandTree(node_param[0],node_param[1],doc);

    QDomNode parent_node;
    parent_node = failed_node.parentNode();
    if (node_param[0] == "Reach")
    {
        QDomNode fisrt_child_node = parent_node.firstChild();
        parent_node.toElement().insertBefore(new_subtree,fisrt_child_node.toElement());
    }
    else
    {
        parent_node.toElement().replaceChild(new_subtree,failed_node.toElement());
    }
    
    //improve goal conditions priority
    if (!NodesForPrior.isEmpty())
    {
        for (int i = 0; i < NodesForPrior.count(); i++)
        {
            QDomElement element_p = doc.createElement("On");
            element_p.setAttribute("text", NodesForPrior[i]);
            QDomNode remove_node;
            QString node_name = "On";
            LocateNode(node_name,NodesForPrior[i],node,remove_node);
            QDomNode p_remove_node;
            p_remove_node = remove_node.parentNode();
            p_remove_node.toElement().removeChild(remove_node);
            node.toElement().insertBefore(element_p,node.firstChild());
        }
        NodesForPrior.clear();
    }

    expansion_duration = time_for_expansion.elapsed();
    qDebug() << "Expansion Time: " << expansion_duration << "ms\n";
    expansion_duration= 0;

    if(!WriteTree(doc))
    {
        return false;
    }
    return true;
}

QDomElement RunBT::ExpandTree(QString node_name, QString node_attribute,QDomDocument& doc)
{
    QDomElement fall_element = doc.createElement("Fallback");
    fall_element.setAttribute("text", "IFTHENELSE");

    if(node_name == "Hold")
    {
        QStringList attribute = node_attribute.split(",");
        
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("HandEmpty");
        element_2.setAttribute("text", node_attribute);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("Near");
        element_3.setAttribute("text", node_attribute);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("Approach");
        element_4.setAttribute("text", node_attribute);
        seq_element.appendChild(element_4);

        QDomElement element_5 = doc.createElement("Pick");
        element_5.setAttribute("text", node_attribute);
        seq_element.appendChild(element_5);
    }
    else if (node_name == "On")
    {
        QStringList attribute = node_attribute.split(",");
        QString attribute_row_1 = attribute[0];
        attribute_row_1.append(",");
        attribute_row_1.append(attribute[1]);
        QString attribute_row_2 = attribute[0];
        attribute_row_2.append(",");
        attribute_row_2.append(attribute[2]);

        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("Hold");
        element_2.setAttribute("text", attribute_row_1);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("Near");
        element_3.setAttribute("text", attribute_row_2);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("Approach");
        element_4.setAttribute("text", attribute_row_2);
        seq_element.appendChild(element_4);

        QDomElement element_5 = doc.createElement("Place");
        element_5.setAttribute("text", node_attribute);
        seq_element.appendChild(element_5);
    }
    else if (node_name == "Near")
    {
        QStringList attribute = node_attribute.split(",");

        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("ExistPath");
        element_2.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("MoveTo");
        element_3.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_3);
    }
    else if (node_name == "Approach")
    {
        QStringList attribute = node_attribute.split(",");

        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        //Search for goal conditions that can be prioritized
        std::string res =  vrep_utilities::GetCurrentObstacle(attribute[0].toStdString());
        QString obstacle_set = QString::fromStdString(res);
        NodesForPrior = Adaptive(obstacle_set,attribute[0]);

        QDomElement element_2 = doc.createElement("HandEmpty");
        element_2.setAttribute("text", attribute[0]);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("Remove");
        QString remove_attribute = node_attribute;
        remove_attribute.append(",");
        remove_attribute.append("obstacle");
        element_3.setAttribute("text", remove_attribute);
        seq_element.appendChild(element_3);
    }
    else if (node_name == "HandEmpty")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Drop");
        seq_element.setAttribute("text", node_attribute);
        fall_element.appendChild(seq_element);

    }
    return fall_element;
}

QStringList RunBT::Adaptive(QString obstacle_set, QString node_attribute)
{
    QStringList Nodes;
    QStringList obstacle = obstacle_set.split(",");
    for (int i = 0; i < obstacle.count(); i++)
    {
        for (int j = 0; j < localgoals.count(); j++)
        {
            QString textContent = localgoals.at(j).toElement().attribute("text");
            QStringList localgoal = textContent.split(",");
            if (obstacle[i] == localgoal[0])
            {
                if (node_attribute == localgoal[1])
                {
                    break;
                }
                Nodes.append(textContent);
            }
        }
    }
    return Nodes;
}

bool RunBT::ReadTree(QDomDocument &doc)
{
    if(first_readtree)
    {
        QStringList file_name = fileName.split("-");
        fileName = file_name[0]+".xml";
    }
    QFile file(fileName);
    if(! file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open XML File False \n";
        return false;
    }
    if(!doc.setContent(&file))
    {
        qDebug() << "Read XML False \n";
        file.close();
        return false;
    }
    file.close();
    if(first_readtree)
    {
        QStringList file_name = fileName.split(".");
        fileName = file_name[0]+"-update.xml";
        first_readtree = false;
    }
    return true;
}

bool RunBT::WriteTree(QDomDocument doc)
{
   QFile file_t(fileName);
    if(!file_t.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Open XML File False \n";
        return false;
    }
    QTextStream ts(&file_t);
    ts.reset();
    // ts.setCodec("utf-8");
    doc.save(ts,4,QDomNode::EncodingFromTextStream);
    file_t.close();
    return true;
}

void RunBT::LocateNode(QString node_name, QString node_attribute,const QDomNode &node, QDomNode &fail_node)
{
    if(node.hasChildNodes())
    {
        for (int i = 0; i < node.childNodes().size(); i++)
        {
            LocateNode(node_name, node_attribute, node.childNodes().at(i),fail_node);   
        }
    }
    else
    {
        if (node.toElement().tagName() == node_name)
        {
            if (node.toElement().attribute("text") == node_attribute)
            {
                qDebug() << "Locate the Node: " << node.toElement().tagName() << " " <<node.toElement().attribute("text");
                fail_node =  node;
            }
        }
    }
}

