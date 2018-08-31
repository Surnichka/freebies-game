cmake_minimum_required(VERSION 2.8)
project(freebies-game)

set(CMAKE_CXX_STANDARD 14)

add_executable(freebies-game "main.cpp")
add_subdirectory(libs)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/SFML/cmake/Modules/")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

IF( NOT SFML_FOUND )
   message( FATAL_ERROR "\nLibrary SFML is not installed!")
ENDIF()

target_link_libraries(freebies-game PRIVATE
                      byte_stream
                      xml_parser
                      resource_mgr
                      sprite
                      tweeny
                      ${SFML_LIBRARIES} )

target_include_directories(freebies-game PRIVATE ${SFML_INCLUDE_DIR})
