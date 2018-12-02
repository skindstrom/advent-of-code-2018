cmake_minimum_required(VERSION 3.02) 
project(aoc-day-02)

find_package(range-v3 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/../third-party)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)

add_executable(day-02 day-02.cpp)
target_link_libraries(day-02 range-v3)
