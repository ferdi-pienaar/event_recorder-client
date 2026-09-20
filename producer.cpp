/*
 */
#include "producer.h"
#include "record_table_event_itf.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h> // sleep

void Producer::start()
{
    pthread_t thread;
    pthread_create(&thread, nullptr, &thread_entry, this);
}

void *Producer::thread_entry(void *arg)
{
    auto self = static_cast<Producer *>(arg);

    while (true)
    {
        sleep(1);
        self->send();
    }
    return nullptr;
}

void Producer::send()
{
    Event &event = m_event_table.get_write_entry();
    event.begin();

    // msg will freed by the consumer.
    Message *msg = new Message(event);

    bool sent = false;
    do
    {
        // If queue is full, wait and try again, since the consumer may have emptied the queue.
        sent = m_queue.enq(msg);
        if (not sent)
        {
            // std::cout << "TX " << msg->id << " failed: sleep and try again." << std::endl;
            sleep(1);
        }
    } while (not sent);
}
