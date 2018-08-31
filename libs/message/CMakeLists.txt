cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_library(message SHARED
                     Message.cpp
                     Message.h)

target_include_directories(message INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_link_libraries(message byte_stream)
