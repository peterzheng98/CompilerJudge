cmake_minimum_required(VERSION 3.14)
project(JudgeBackend)

set(CMAKE_CXX_STANDARD 14)


add_library(JSON jsoncpp.cpp)
add_executable(JudgeBackend main.cpp init.cpp init.h Utility.h)
target_link_libraries(JudgeBackend JSON)