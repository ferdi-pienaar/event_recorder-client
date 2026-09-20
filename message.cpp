/*
 *
 */
#include "event.h"
#include <new> // bad_alloc

static EventMsgPool msg_pool;

unsigned Message::c_id = 0;

// Override operator new
void *Message::operator new(std::size_t size)
{
    uint8_t *p = msg_pool.get_buf();
    if (!p)
        throw std::bad_alloc();
    return p;
}

// Override operator delete
void Message::operator delete(void *p) noexcept
{
    EventMsgPool::put_buf(reinterpret_cast<uint8_t *>(p));
}
