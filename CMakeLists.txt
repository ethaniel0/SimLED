cmake_minimum_required(VERSION 3.26)
project(SimLED)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(FastLED)
add_subdirectory(ObjectSystem)

set(LIBXD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libxd")

include_directories(${LIBXD_PATH}/include)

add_executable(SimLED main.cpp)

target_link_libraries(SimLED PRIVATE
        ${LIBXD_PATH}/lib/libxd.a
        ${LIBXD_PATH}/lib/libglad.a
        ${LIBXD_PATH}/lib/libglfw3.a
)

if(APPLE)
    target_link_libraries(SimLED PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreVideo"
    )
endif()

target_link_libraries(SimLED PRIVATE FastLED)
target_link_libraries(SimLED PRIVATE ObjectSystem)
target_include_directories(SimLED PRIVATE ${LIBXD_PATH}/include)
