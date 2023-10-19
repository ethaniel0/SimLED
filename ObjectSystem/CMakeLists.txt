cmake_minimum_required(VERSION 3.5)

set(ObjectSystem_SRCS
        LightStrip.cpp
        LightObject.cpp
        ObjectSystem.cpp
        animations/Animation.cpp
        animations/AnimationFunctions.cpp
        animations/BaseAnimation.cpp
        animations/AnimationGroups.h
        animations/AnimationGroups.cpp
)

add_library(ObjectSystem ${ObjectSystem_SRCS})

target_include_directories(ObjectSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

project(ObjectSystem)
