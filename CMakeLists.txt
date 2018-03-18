cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(prism)

add_definitions(-std=c++11)

if (WIN32)

    set(PRISM_BASE_LIB_NAME libprismbase)
    set(PRISM_BASE_INC_PATH C:/Users/Iain/GitHub/PrismBase/inc)
    set(PRISM_BASE_LIB_PATH C:/Users/Iain/GitHub/PrismBase/build)

    # set(GMOCK_LIB_NAME libgmock)
    # set(GMOCK_INC_PATH C:/Users/Iain/GitHub/googletest/googlemock/include)
    # set(GMOCK_LIB_PATH C:/Users/Iain/GitHub/googletest/build/googlemock)
    #
    # set(GTEST_LIB_NAME libgtest)
    # set(GTEST_INC_PATH C:/Users/Iain/GitHub/googletest/googletest/include)
    # set(GTEST_LIB_PATH C:/Users/Iain/GitHub/googletest/build/googlemock/gtest)

endif()

include_directories(
    inc
    ${PRISM_BASE_INC_PATH}
    ${GMOCK_INC_PATH}
    ${GTEST_INC_PATH}
)

find_library(
    PRISM_BASE_LIB
    NAMES ${PRISM_BASE_LIB_NAME}
    PATHS ${PRISM_BASE_LIB_PATH}
)

# find_library(
#     GMOCK_LIB
#     NAMES ${GMOCK_LIB_NAME}
#     PATHS ${GMOCK_LIB_PATH}
# )
#
# find_library(
#     GTEST_LIB
#     NAMES ${GTEST_LIB_NAME}
#     PATHS ${GTEST_LIB_PATH}
# )

include(sources.cmake)
add_library(prism STATIC ${SOURCES})
target_link_libraries(
    prism
    ${PRISM_BASE_LIB} ${GMOCK_LIB} ${GTEST_LIB}
)
