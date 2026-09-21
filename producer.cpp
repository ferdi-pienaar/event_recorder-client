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
        send();
        // Try to start the next event 1 sec after this one, regardles of how long send took.
        std::this_thread::sleep_until(next_send_time);
    }
}

void Producer::send()
{
    Event &event = m_event_table.get_write_entry();
    event.begin();

    // msg will freed by the consumer.
    Message *msg = new Message(event);
    // std::cout << "TX " << msg->id << std::endl;
    bool sent = false;
    do
    {
        // If queue is full, wait for the consumer to empty the queue and try again.
        sent = m_queue.enq(msg);
        if (not sent)
        {
            // std::cout << "TX " << msg->id << " failed: sleep and try again." << std::endl;
            std::this_thread::sleep_for(milliseconds(500));
        }
    } while (not sent);
}
