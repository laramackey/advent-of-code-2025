
cmake_minimum_required(VERSION 4.0.0)

project(advent_of_code_day1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day1 main.cpp)

add_custom_command(
        TARGET day1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/input.txt
        $<TARGET_FILE_DIR:day1>
)