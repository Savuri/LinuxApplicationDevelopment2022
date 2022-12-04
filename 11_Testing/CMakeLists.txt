cmake_minimum_required(VERSION 3.22)
project(GrowableBuf C)

set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -O3 -g3 ${CMAKE_C_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "-std=c99 -Wno-deprecated-register -O0 -g -fprofile-arcs -ftest-coverage --coverage ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g3 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-Wno-deprecated-register -O0 -g -fprofile-arcs -ftest-coverage --coverage ${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

enable_testing()
find_package(GTest REQUIRED)
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(distclean COMMAND git clean -df)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_custom_target(coverage
        COMMAND make all test
        COMMAND gcov tests/CMakeFiles/growable_buf_test.dir/tests.cpp.gcno
        COMMAND lcov --capture --directory src/. --output-file gtest_coverage.info
        COMMAND genhtml gtest_coverage.info --output-directory CODE_COVERAGE
        COMMAND firefox CODE_COVERAGE/index.html
        )
else()
    add_custom_target(coverage
            COMMAND echo No coverage in relese build
            COMMAND echo Build cmake as debug project
            COMMAND echo cmake .. -DCMAKE_BUILD_TYPE=Debug
            )
endif()