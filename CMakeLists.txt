cmake_minimum_required(VERSION 3.28)
project(regex-c-fr VERSION 0.1.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -glldb")

file(GLOB C_SOURCES src/*.c)
add_executable(regex-c-fr ${C_SOURCES})

