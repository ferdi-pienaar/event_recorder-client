/*
 * 
 */
#include "record_table.h"
#include "record_table_manager.h"
#include <iostream>

void dump_table_state_cb(const Record_table_op_itf & t)
{
    std::cout << "size " << t.size() << std::endl;
    std::cout << "enabled " << t.enabled() << std::endl;
    std::cout << "oneshot " << t.oneshot() << std::endl;
    std::cout << "written entries " << t.get_num_written_entries() << std::endl;
    std::cout << "stopped " << t.is_stopped() << std::endl;
}

int main(int argc, char * argv[])
{
    Record_table<int> itable(Record_table_init_config().size(2).enable(), nullptr, dump_table_state_cb);
    Record_table_manager table_mgr({{"int_table", itable}});

    itable.get_write_entry() = 1;
    table_mgr.dump_tables_state("int_table");
    return 0;
}
