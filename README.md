# Introduction
This project is an example client of these libraries:
- [event_recorder](https://github.com/ferdi-pienaar/event_recorder)
- [seq_buf_pool](https://github.com/ferdi-pienaar/seq_buf_pool)
- [strqueue](https://github.com/ferdi-pienaar/strqueue)

The producer thread creates an event and writes the begin-time of event-processing to an entry in an event_recorder Table. The producer then sends a reference to the event in a message that's received by the consumer thread. The consumer thread updates the event in the event_recorder Table with the end-time of the event processing.

The operator can display the recorded events, showing the varying delays between the beginning and end of event-handling.

```mermaid
---
config:
  layout: elk
  class:
    hideEmptyMembersBox: true
---

classDiagram

    Table *--> Event
    Producer --> EventMsgQueue : sends Messages to
    Consumer --> EventMsgQueue : receives Messages from
    Producer --> Event : writes to
    Consumer --> Event : writes to
    Producer --> Message : allocates and sends
    Consumer --> Message : receives and frees
    Message --> EventMsgPool : allocates memory from

    namespace Event_record {
        class TableManager
        class Table
    }

    TableManager --> Table : manages
    Producer --> Table : gets Event from
    Operator --> TableManager : displays and manages Table

```

# Building
To use libraries installed in non-standard location, configure like this:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH=<install/path>
```
