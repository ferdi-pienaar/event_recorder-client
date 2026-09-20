cmake_minimum_required(VERSION 3.16)
project(event_generator
    VERSION 1.0
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(event_recorder REQUIRED)
find_package(seq_buf_pool REQUIRED)
find_package(strqueue REQUIRED)

add_executable(event_generator
    composition_root.cpp
    operator.cpp
    operator_helper.cpp
    producer.cpp
    consumer.cpp
    message.cpp
)

target_link_libraries(event_generator
    PRIVATE
        event_recorder::event_recorder
        seq_buf_pool::seq_buf_pool
        strqueue::strqueue
)
