cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(prism)

add_definitions(-std=c++11)

if (WIN32)

    set(PRISM_BASE_LIB_NAME libprismbase)
    set(PRISM_BASE_INC_PATH C:/Users/Iain/GitHub/PrismBase/inc)
    set(PRISM_BASE_LIB_PATH C:/Users/Iain/GitHub/PrismBase/build)

elseif(APPLE)

    set(PRISM_BASE_LIB_NAME prismbase)
    set(PRISM_BASE_INC_PATH /Users/iainhemstock/GitHub/PrismBase/inc)
    set(PRISM_BASE_LIB_PATH /Users/iainhemstock/GitHub/PrismBase/build)

endif()

include_directories(
    inc
    ${PRISM_BASE_INC_PATH}
)

find_library(
    PRISM_BASE_LIB
    NAMES ${PRISM_BASE_LIB_NAME}
    PATHS ${PRISM_BASE_LIB_PATH}
)

include(sources.cmake)
add_library(prism STATIC ${SOURCES})
target_link_libraries(prism ${PRISM_BASE_LIB})
