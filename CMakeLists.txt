cmake_minimum_required(VERSION 3.29)
project(automata VERSION 1.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -glldb")

file(GLOB ENGINE_SOURCES engine/*.c)
add_executable(automata main.c ${ENGINE_SOURCES})


set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/examples)
add_custom_command(TARGET automata POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${EXAMPLES_DIR}"
        "$<TARGET_FILE_DIR:automata>/examples"
)

