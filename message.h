/*
 *
 */
#pragma once
#include <cstddef>

struct Event;

// Msg carries an ID and a reference to Event.
struct Message
{
    Message(Event &e) : id(c_id++), event(&e) {}
    void *operator new(std::size_t size);
    void operator delete(void *p) noexcept;

    unsigned id;
    Event *event;
    static unsigned c_id;
};
