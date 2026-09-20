/*
 */
#include "event.h"

namespace Event_record
{
template <typename ENTRY> class Table_event_itf;
}

class Consumer
{
public:
    Consumer(EventMsgQueue &q) : m_queue(q) {}

    void start();

private:
    static void *thread_entry(void *);
    void receive();
    void end_event(Event &event);

    EventMsgQueue &m_queue;
};
