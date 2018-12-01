cmake_minimum_required(VERSION 3.1) 
project(aoc-day-1)

find_package(range-v3 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)

add_executable(day-1 day-1.cpp)
target_link_libraries(day-1 range-v3)
