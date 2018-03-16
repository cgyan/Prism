cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(prism)

add_definitions(-std=c++11)

include_directories(
    c:/inc
    inc
)

include(sources.cmake)
add_library(prism STATIC ${SOURCES})

find_library(PRISM_BASE_LIB libprismbase)
target_link_libraries(prism ${PRISM_BASE_LIB})
