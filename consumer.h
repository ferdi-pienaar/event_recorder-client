/*
 */
#include "queue.h"
#include <thread>

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
    void thread_entry();
    void receive();

    EventMsgQueue &m_queue;
    std::thread m_thread;
};
