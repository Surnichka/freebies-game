cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_library(events SHARED ${SOURCES})

target_include_directories(events INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_link_libraries(events)
