cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(prism_d)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# turn off optimizations
# seems to be causing a problem with gdb when turned on
SET(CMAKE_CXX_FLAGS "-O0")

if (WIN32)

    set(PRISM_BASE_INC_PATH C:/Users/Iain/GitHub/PrismBase/inc)

elseif(APPLE)

    set(PRISM_BASE_INC_PATH /Users/iainhemstock/GitHub/PrismBase/inc)

endif()

include_directories(
    inc
    ${PRISM_BASE_INC_PATH}
)

include(sources.cmake)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})
