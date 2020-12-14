cmake_minimum_required(VERSION 3.10)

SET(SOURCE_WAY src)

add_executable(matrix ${SOURCE_WAY}/main.cpp)

target_include_directories(matrix PRIVATE 
                                  inc)                