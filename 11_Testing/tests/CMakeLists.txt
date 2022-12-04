project(tests)

find_package(GTest REQUIRED)

add_executable(growable_buf_test tests.cpp)
target_link_libraries(growable_buf_test GTest::gtest_main)
target_link_libraries(growable_buf_test gbuf)

gtest_discover_tests(growable_buf_test)