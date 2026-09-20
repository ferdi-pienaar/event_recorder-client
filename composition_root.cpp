/*
 *
 */
#include "consumer.h"
#include "event.h"
#include "operator.h"
#include "operator_helper.h"
#include "producer.h"
#include "record_table.h"
#include "record_table_manager.h"
#include <iostream>

using namespace Event_record;

int main(int argc, char *argv[])
{
    Table<Event> ttable(Table_init_config().size(20).enable(), dump_event_cb, dump_table_state_cb);
    Table_manager table_mgr({{"time", ttable}}, operator_out_cb);

    EventMsgQueue msg_queue;

    Producer tx(ttable, msg_queue);
    tx.start();

    Consumer rx(msg_queue);
    rx.start();

    Operator oper(table_mgr);
    oper.run();
    return 0;
}
