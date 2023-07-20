cmake_minimum_required(VERSION 3.5)

project(demo)

add_executable(demo demo.cpp)

target_include_directories(demo
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
