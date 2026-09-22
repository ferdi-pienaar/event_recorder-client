/*
 */
#include "producer.h"
#include "message.h"
#include "record_table_event_itf.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

void Producer::start()
{
    m_thread = std::thread(&Producer::thread_entry, this);
}

void Producer::thread_entry()
{
    while (true)
    {
        auto next_send_time = steady_clock::now() + milliseconds(1000);
        produce_event();
        // Try to start the next event 1 sec after this one, regardles of how long send took.
        std::this_thread::sleep_until(next_send_time);
    }
}

void Producer::produce_event()
{
    Event &event = m_event_table.get_write_entry();
    event.begin();

    bool sent = false;
    while (not sent)
    {
        try
        {
            // msg will freed by the consumer.
            sent = send(new Message(event));
        }
        catch (const std::bad_alloc &e)
        {
            // Pool is empty, wait for the consumer to put buffers and try again.
            std::cerr << "Allocation failed: " << e.what() << std::endl;
            std::this_thread::sleep_for(milliseconds(500));
        }
    }
}

// todo: timeout or repeat counter after which we fail, but note that this function
// owns the msg, so that a simple abort would be a resource leak.
bool Producer::send(Message *msg)
{
    // std::cout << "TX " << msg->id << std::endl;
    while (true)
    {
        if (m_queue.enq(msg))
        {
            return true;
        }
        std::cout << "TX " << msg->id << " enq failed: sleep and try again." << std::endl;
        std::this_thread::sleep_for(milliseconds(500));
    }
    return false;
}
