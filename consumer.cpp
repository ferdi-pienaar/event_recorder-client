/*
 */
#include "consumer.h"
#include "record_table_event_itf.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h> // sleep

void Consumer::start()
{
    pthread_t thread;
    pthread_create(&thread, nullptr, &thread_entry, this);
}

void *Consumer::thread_entry(void *arg)
{
    auto self = static_cast<Consumer *>(arg);
    while (true)
    {
        sleep(5);
        self->receive();
    }
    return nullptr;
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
