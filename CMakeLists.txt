cmake_minimum_required(VERSION 2.8)
project(freebies-game)

set(CMAKE_CXX_STANDARD 14)

add_executable(freebies-game "main.cpp")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/SFML/cmake/Modules/")

add_subdirectory(Core)

target_include_directories(freebies-game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Thor/include")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

IF( NOT SFML_FOUND )
   message( FATAL_ERROR "\nLibrary SFML is not installed!")
ENDIF()

target_link_libraries(freebies-game PRIVATE
                      ${SFML_LIBRARIES}
                      Core)

target_include_directories(freebies-game PRIVATE ${SFML_INCLUDE_DIR}) 
