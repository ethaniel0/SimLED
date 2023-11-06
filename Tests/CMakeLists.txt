cmake_minimum_required(VERSION 3.26)
project(SimLEDTests)

set(CMAKE_CXX_STANDARD 11)

set(TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TESTS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${TESTS_SOURCE_DIR}/../FastLED ${TESTS_BINARY_DIR}/FastLED)
add_subdirectory(${TESTS_SOURCE_DIR}/../ObjectSystem ${TESTS_BINARY_DIR}/ObjectSystem)
add_subdirectory(${TESTS_SOURCE_DIR}/../Graphics ${TESTS_BINARY_DIR}/Graphics)


set(LIBXD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../libxd")

include_directories(${LIBXD_PATH}/include)



add_executable(
        SimLEDTests tests.cpp
        Tests/LightObjTests.cpp
        Framework/TestFramework.h
        Framework/TestFramework.cpp
        Tests/StripTests.cpp
        Tests/AnimationTests.cpp
        Tests/AnimationFunctionTests.cpp
)

target_link_libraries(SimLEDTests PRIVATE
        ${LIBXD_PATH}/lib/libxd.a
        ${LIBXD_PATH}/lib/libglad.a
        ${LIBXD_PATH}/lib/libglfw3.a
)

if(APPLE)
    target_link_libraries(SimLEDTests PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreVideo"
    )
endif()

target_link_libraries(SimLEDTests PRIVATE FastLED)
target_link_libraries(SimLEDTests PRIVATE ObjectSystem)
target_link_libraries(SimLEDTests PRIVATE Graphics)
target_include_directories(SimLEDTests PRIVATE ${LIBXD_PATH}/include)
