/*
 */
#include "consumer.h"
#include "event.h"
#include "message.h"
#include "record_table_event_itf.h"
#include <chrono>

using namespace std::chrono;

void Consumer::start()
{
    m_thread = std::thread(&Consumer::thread_entry, this);
}

void Consumer::thread_entry()
{
    while (true)
    {
        std::this_thread::sleep_for(milliseconds(4500));
        receive();
    }
}

void Consumer::receive()
{
    // Handle all the messages in the queue.
    Message *msg = nullptr;
    while (m_queue.deq(msg))
    {
        // std::cout << "RX: " << msg->id << std::endl;
        msg->event->end();

        // Free msg that was allocated by the consumer.
        delete (msg);
    }
}
