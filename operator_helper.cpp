/*
 * Helper functions used by the operator that manages and dumps the record tables.
 * It depends only on the abstract interface record_table_op_itf.h.
 */
#include "operator_helper.h"
#include "record_table_op_itf.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace Event_record;
using namespace std::chrono;

void dump_event_cb(const Event &event)
{
    if (event.m_end)
    {
        // 'end' entry has been written, so show diff.
        auto elapsed = duration_cast<nanoseconds>(event.stamp[1] - event.stamp[0]);
        std::cout << "elapsed [ns]: " << std::setfill('0') << std::setw(10) << elapsed.count()
                  << std::endl;
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
