#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <node_editor/Node>
#include <QDomDocument>
#include <QShortcut>
#include <QTimer>
#include <deque>
#include <thread>
#include <mutex>
#include <QStringList>
#include "RunBT.h"
#include "utils.h"

namespace Ui {
class MainWindow;
}

namespace QtNodes{
class FlowView;
class FlowScene;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_ut_triggered();

    void on_actionAuto_arrange_triggered();

    void onNodeMoved();

    void onNodeSizeChanged();

    virtual void closeEvent(QCloseEvent *event) override;

    void onTimerUpdate();

    void on_playButton_released();

    void re_execute();

signals:
    void updateGraphic();

private:
    Ui::MainWindow *ui;

    void lockEditing(const bool locked);

    void updateStates(QXmlInputSource* source);

    QtNodes::FlowScene* _main_scene;
    QtNodes::FlowView*  _main_view;

    bool _node_moved;

    QShortcut _arrange_shortcut;

    void recursivelyCreateXml(QDomDocument& doc, QDomElement& parent_element, const QtNodes::Node* node);

    QTimer _periodic_timer;

    std::mutex _mutex;

    void loadFromXML(const QString &xml_text);

    bool ReConstructTree();

    void loadInitialTree();

    bool    _state_received;
    QString _state_msg;
    QtNodes::Node* _root_node;
    RunBT *run_bt;
    QString fileName;

};

#endif // MAINWINDOW_H
