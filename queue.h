/*
 *
 */
#pragma once
#include "strqueue.h"

struct Message;

constexpr unsigned QUEUE_LEN = 8;

// The queue carries pointers to the buffers containing Messages, not Messages themselves.
using EventMsgQueue = StreamQueue::queue<Message *, QUEUE_LEN>;
