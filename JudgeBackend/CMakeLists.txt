cmake_minimum_required(VERSION 3.14)
project(JudgeBackend)

set(CMAKE_CXX_STANDARD 14)

add_library(Core JudgeCore.cpp Macros.h)
add_executable(JudgeCore main.cpp Macros.h)
target_link_libraries(JudgeCore Core)