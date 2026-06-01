cmake_minimum_required(VERSION 3.16...3.30)
project(untitled C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(untitled main.c logic.c simulation.c ui.c)

target_link_libraries(untitled PRIVATE SDL3::SDL3)