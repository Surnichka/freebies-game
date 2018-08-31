cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_library(xml_parser SHARED ${SOURCES})

target_include_directories(xml_parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_link_libraries(xml_parser byte_stream)
