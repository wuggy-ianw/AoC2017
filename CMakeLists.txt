cmake_minimum_required(VERSION 3.9)
project(AoC2017)

set(CMAKE_CXX_STANDARD 11)

include(cmake/googletest-build.cmake)
enable_testing()

add_subdirectory(day01)
