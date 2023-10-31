cmake_minimum_required(VERSION 3.5)

set(Arduino_SRCS
        Arduino.cpp
)

add_library(Arduino ${Arduino_SRCS})

target_include_directories(Arduino PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

project(Arduino)
