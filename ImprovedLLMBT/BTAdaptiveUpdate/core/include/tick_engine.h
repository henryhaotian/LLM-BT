#ifndef TICK_ENGINE_H
#define TICK_ENGINE_H



#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>

class TickEngine
{


public:
    TickEngine(int initial_value);
    ~TickEngine();
    void Wait();
    void Tick();
    class SyncLink
    {
    private:
        std::string name_;
        unsigned int number_of_nodes_;
        unsigned int number_of_nodes_done_;
        unsigned int current_tick_id_;
        std::mutex current_tick_id_mutex_;

    public:
        SyncLink(std::string name);
        ~SyncLink();
        bool is_tick_id_ready(unsigned int tick_id);
        void NodeDone(unsigned int tick_id);
    };
    SyncLink* CreateSyncLink(std::string name);


private:
    int value_;
    std::mutex mutex_;
    std::condition_variable condition_variable_;
    std::vector<std::string> sync_link_name_vec_;


    std::vector<TickEngine::SyncLink*> sync_link_vec_;
};



#endif
