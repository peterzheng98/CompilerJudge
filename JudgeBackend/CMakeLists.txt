cmake_minimum_required(VERSION 3.14)
project(JudgeBackend)

set(CMAKE_CXX_STANDARD 14)


#add_library(judgeThread judgeThread.cpp)
add_library(JSON jsoncpp.cpp judgeRun.cpp judgeRun.h)
add_library(Init init.cpp jsoncpp.cpp test.cpp)
add_executable(JudgeBackend main.cpp init.cpp init.h Utility.h judgeRun.cpp judgeRun.h)
target_link_libraries(JudgeBackend JSON sqlite3 pthread)