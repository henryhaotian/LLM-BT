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
            emit ReExecute();
            return;
        }
    }
    std::cout << "Halting the BT" << std::endl;
    bt_root->Halt();
}

bool RunBT::UpdateTree(QString fail_node)
{
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

    QDomNode failed_node;
    LocateNode(node_param[0],node_param[1],node,failed_node);

    QDomElement new_subtree = ExpandTree(node_param[0],node_param[1],doc);

    QDomNode parent_node;
    parent_node = failed_node.parentNode();
    if (node_param[0] == "IsPathToDestination")
    {   
        QDomNode fisrt_child_node = parent_node.firstChild();
        parent_node.toElement().insertBefore(new_subtree,fisrt_child_node.toElement());
    }
    else
    {
        parent_node.toElement().replaceChild(new_subtree,failed_node.toElement());
    }
    
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

    /* insert new rule for constructing subtree*/
    if(node_name == "IsObjectOnHand")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("IsHandEmpty");
        element_2.setAttribute("text", node_attribute);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("IsFind");
        element_3.setAttribute("text", node_attribute);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("IsPathToObject");
        element_4.setAttribute("text", node_attribute);
        seq_element.appendChild(element_4);

        QDomElement element_5 = doc.createElement("Pick");
        element_5.setAttribute("text", node_attribute);
        seq_element.appendChild(element_5);
    }
    else if (node_name == "IsObjectOnDestination")
    {
        QStringList attribute = node_attribute.split(",");

        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("IsObjectOnHand");
        element_2.setAttribute("text", attribute[0]);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("IsFind");
        element_3.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("IsPathToDestination");
        element_4.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_4);

        QDomElement element_5 = doc.createElement("Place");
        element_5.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_5);
    }

    return fall_element;
}

bool RunBT::ReadTree(QDomDocument &doc)
{
    if(first_readtree)
    {
        QStringList file_name = fileName.split("update");
        fileName = file_name[0]+"initial.xml";
        // qDebug() << fileName << "\n";
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
        QStringList file_name = fileName.split("initial");
        fileName = file_name[0]+"update.xml";
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
                qDebug() << " Find The Failed Node";
                fail_node =  node;
            }
        }
    }
}
