/*
 *
 */
#pragma once

#include "message.h"
#include "seq_buf_pool.h"

constexpr unsigned NUM_BUFS = 10;

using EventMsgPool = SeqBufPool::Pool<NUM_BUFS, sizeof(Message)>;
