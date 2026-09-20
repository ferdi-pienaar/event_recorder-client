/*
 */
#include "event.h"

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
    static void *thread_entry(void *);
    void send();
    void begin_event(Event &event);

    Event_record::Table_event_itf<Event> &m_event_table;
    EventMsgQueue &m_queue;
};
