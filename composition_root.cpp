/*
 *
 */
#include "record_table.h"
#include "record_table_manager.h"
#include <iostream>

void dump_table_state_cb(const Event_record::Table_op_itf &t)
{
    std::cout << "size " << t.size() << std::endl;
    std::cout << "enabled " << t.enabled() << std::endl;
    std::cout << "oneshot " << t.oneshot() << std::endl;
    std::cout << "written entries " << t.get_num_written_entries() << std::endl;
    std::cout << "stopped " << t.is_stopped() << std::endl;
}

void dump_entry(const int &entry)
{
    std::cout << entry << std::endl;
}

void operator_out(const std::string &msg)
{
    std::cout << msg;
}

int main(int argc, char *argv[])
{
    Event_record::Table<int> itable(Event_record::Table_init_config().size(2).enable(), dump_entry,
                                    dump_table_state_cb);
    Event_record::Table_manager table_mgr({{"int_table", itable}}, operator_out);

    itable.get_write_entry() = 1;
    itable.get_write_entry() = 121;

    // Lambda returns true always, i.e. apply command to all tables.
    auto matcher = [](const std::string &name) { return true; };

    table_mgr.enable_tables(matcher, false);
    table_mgr.dump_tables_state(matcher);
    table_mgr.dump_tables(matcher);
    return 0;
}
