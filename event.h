/*
 *
 */
#pragma once
#include <array>
#include <chrono>

// Event two timestamps, the begin and end of event processing.
struct Event
{
    // Set begin and invalidate end.
    void begin()
    {
        stamp[0] = std::chrono::steady_clock::now();
        m_end = false;
    }

    void end()
    {
        stamp[1] = std::chrono::steady_clock::now();
        m_end = true;
    }

    std::array<std::chrono::steady_clock::time_point, 2> stamp;
    bool m_end = false;
};
