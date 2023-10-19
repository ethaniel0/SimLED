# FastLED
# https://github.com/FastLED/FastLED
# MIT License

cmake_minimum_required(VERSION 3.5)

set(FastLED_SRCS
  src/bitswap.cpp
  src/colorpalettes.cpp
  src/colorutils.cpp
  src/FastLED.cpp
  src/hsv2rgb.cpp
  src/lib8tion.cpp
  src/noise.cpp
  )

add_library(FastLED ${FastLED_SRCS})

target_include_directories(FastLED PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

project(FastLED)
