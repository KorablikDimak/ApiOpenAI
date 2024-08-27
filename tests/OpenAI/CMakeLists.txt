cmake_minimum_required(VERSION 3.5)

project(OpenAI-tests)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    enable_testing()
    find_package(OpenAI REQUIRED)
endif()

find_package(GTest REQUIRED)

set(OpenAI_TESTS_SOURCES
        main.cpp
        NoThrowTests.cpp)

add_executable(OpenAI-tests ${OpenAI_TESTS_SOURCES})
target_link_libraries(OpenAI-tests PRIVATE OpenAI::OpenAI GTest::gtest GTest::gtest_main)