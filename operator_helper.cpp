/*
 * Helper functions used by the operator that manages and dumps the record tables.
 * It depends only on the abstract interface record_table_op_itf.h.
 */
#include "operator_helper.h"
#include "record_table_op_itf.h"
#include <iostream>
#include <string>

using namespace Event_record;

static double diff_timespec(const timespec &t0, const timespec &t1)
{
    return (t1.tv_sec - t0.tv_sec) + 1.0e-9 * (t1.tv_nsec - t0.tv_nsec);
}

void dump_event_cb(const Event &event)
{
    for (auto const &t : event.stamp)
    {
        std::cout << t.tv_sec << "." << t.tv_nsec << std::endl;
    }
    if (!((event.stamp[1].tv_sec == 0) && (event.stamp[1].tv_nsec == 0)))
    {
        // 'end' entry has been written, so show diff.
        std::cout << "elapsed: " << diff_timespec(event.stamp[0], event.stamp[1]) << std::endl;
    }
    else
    {
        std::cout << "event incomplete." << std::endl;
    }
}

void dump_table_state_cb(const Table_op_itf &t)
{
    std::cout << "size " << t.size() << std::endl;
    std::cout << "enabled " << t.enabled() << std::endl;
    std::cout << "oneshot " << t.oneshot() << std::endl;
    std::cout << "written entries " << t.get_num_written_entries() << std::endl;
    std::cout << "stopped " << t.is_stopped() << std::endl;
}

void operator_out_cb(const std::string &msg)
{
    std::cout << msg;
}
