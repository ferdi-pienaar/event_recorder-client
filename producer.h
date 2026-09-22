/*
 */
#include "event.h"
#include "queue.h"
#include <thread>

namespace Event_record
{
template <typename ENTRY> class Table_event_itf;
}

class Producer
{
public:
    Producer(Event_record::Table_event_itf<Event> &t, EventMsgQueue &q)
        : m_event_table(t), m_queue(q)
    {
    }

    void start();

private:
    void thread_entry();
    void produce_event();
    bool send(Message *);

    Event_record::Table_event_itf<Event> &m_event_table;
    EventMsgQueue &m_queue;
    std::thread m_thread;
};
