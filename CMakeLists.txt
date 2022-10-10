cmake_minimum_required(VERSION 3.23)
project(PSO2 C)

set(CMAKE_C_STANDARD 99)

add_executable(PSO2 main.c swarm.c graph.c swarm.h graph.h)
target_link_libraries(PSO2 PRIVATE m)
