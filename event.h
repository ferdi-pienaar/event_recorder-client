/*
 *
 */
#pragma once

#include "seq_buf_pool.h"
#include "strqueue.h"
#include <array>
#include <time.h> // struct timespec

// Event two timestamps, the begin and end of event processing.
struct Event
{
    // Set begin and invalidate end.
    void begin()
    {
        clock_gettime(CLOCK_REALTIME, &(stamp[0]));

        // Invalidate the end timestamp, it will be set by the consumer.
        stamp[1].tv_sec = 0;
        stamp[1].tv_nsec = 0;
    }

    void end()
    {
        timespec &end_stamp = stamp[1];
        // Write the 2nd timestamp to the table.
        clock_gettime(CLOCK_REALTIME, &end_stamp);
    }

    std::array<timespec, 2> stamp;
};

constexpr unsigned NUM_BUFS = 10;
constexpr unsigned QUEUE_LEN = 4;

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

using EventMsgPool = SeqBufPool::Pool<NUM_BUFS, sizeof(Message)>;

// The queue carries pointers to the buffers containing Messages, not Messages themselves.
using EventMsgQueue = queue<Message *, QUEUE_LEN>;
