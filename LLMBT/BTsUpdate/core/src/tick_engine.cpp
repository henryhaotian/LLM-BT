/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <tick_engine.h>

TickEngine::TickEngine(int initial_value)
{
    value_ = initial_value;
}

TickEngine::~TickEngine() {}

void TickEngine::Wait()
{
    // Lock acquire (need a unique lock for the condition variable usage)
    std::unique_lock<std::mutex> UniqueLock(mutex_);

    // If the state is 0 then we have to wait for a signal
    if (value_ == 0)
        condition_variable_.wait(UniqueLock);

    // Once here we decrement the state
    value_--;
}

void TickEngine::Tick()
{
    // Lock acquire

    std::lock_guard<std::mutex> LockGuard(mutex_);

    // State increment
    value_++;

    // Notification
    condition_variable_.notify_all();
}

TickEngine::SyncLink* TickEngine::CreateSyncLink(std::string name)
{
    std::vector<std::string>::iterator pos = std::find(sync_link_name_vec_.begin(), sync_link_name_vec_.end(), name);

    if (pos == sync_link_name_vec_.end()) {
      // the link does not exists, add it
      sync_link_name_vec_.push_back(name);
      sync_link_vec_.push_back(new SyncLink(name));
      return sync_link_vec_.back();
    }
    else
    {
        return sync_link_vec_.at(distance(sync_link_name_vec_.begin(), pos));
    }

}


TickEngine::SyncLink::SyncLink(std::string name)
{
    name_ = name;
    current_tick_id_ = 0;

}

TickEngine::SyncLink::~SyncLink() {}



bool TickEngine::SyncLink::is_tick_id_ready(unsigned int tick_id)
{
    std::lock_guard<std::mutex> LockGuard(current_tick_id_mutex_);

    return tick_id <= current_tick_id_;

}

void TickEngine::SyncLink::NodeDone(unsigned int tick_id)
{
    std::lock_guard<std::mutex> LockGuard(current_tick_id_mutex_);

    if(tick_id != current_tick_id_)
    {
        throw std::string("ERROR IN TICK ID");
    }

    if (++number_of_nodes_done_ == number_of_nodes_)
    {
        current_tick_id_++;
    }

}


