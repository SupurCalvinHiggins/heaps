project(gtest_proj)


add_subdirectory(gtest/googletest-main)
include_directories(googletest/include googletest)


add_executable(gtest_run ../tests/test_heaps.cpp)
target_link_libraries(gtest_run gtest gtest_main)