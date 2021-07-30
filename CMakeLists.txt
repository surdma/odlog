cmake_minimum_required(VERSION 3.18)
project(odlog)

set(CMAKE_CXX_STANDARD 20)
link_libraries( -pthread )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
add_executable(odlog main.cpp Logger.h)