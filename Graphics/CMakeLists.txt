cmake_minimum_required(VERSION 3.5)

set(Graphics_SRCS
        GraphicsUtils.cpp
        StripElement.cpp
        Button.cpp
)

set(LIBXD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../libxd")

include_directories(${LIBXD_PATH}/include)

add_library(Graphics ${Graphics_SRCS})

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Graphics PRIVATE
        ${LIBXD_PATH}/lib/libxd.a
        ${LIBXD_PATH}/lib/libglad.a
        ${LIBXD_PATH}/lib/libglfw3.a
)

if(APPLE)
    target_link_libraries(Graphics PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreVideo"
    )
endif()
target_include_directories(Graphics PRIVATE ${LIBXD_PATH}/include)


project(Graphics)
