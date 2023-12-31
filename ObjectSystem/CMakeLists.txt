cmake_minimum_required(VERSION 3.5)
project(ObjectSystem)

set(ObjectSystem_SRCS
        src/ObjectSystem.cpp
        src/strips/LightStrip.cpp
        src/objects/LightObject.cpp
        src/animations/Animation.cpp
        src/animations/AnimationFunctions.cpp
        src/animations/BaseAnimation.cpp
        src/animations/AnimationGroups.cpp
        src/creators/SystemCreator.cpp
        src/creators/AnimationCreators.cpp
        src/creators/utils.cpp
        src/creators/ObjectCreators.cpp
        src/objects/Generator.cpp
        src/creators/FunctionCreators.cpp
        src/strips/StripPath.cpp
        src/animations/DataReactor.h
        src/objects/ObjectManager.cpp
        src/objects/ObjectGroup.cpp
        src/objects/ObjectStateMap.cpp
)

add_subdirectory(../Arduino src/Arduino)

add_library(ObjectSystem ${ObjectSystem_SRCS})

target_include_directories(ObjectSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ObjectSystem PRIVATE Arduino)


