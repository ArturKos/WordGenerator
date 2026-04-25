cmake_minimum_required(VERSION 3.14)
project(word_generator C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(word_generator_lib STATIC src/word_generator.c)
target_include_directories(word_generator_lib PUBLIC include)

add_executable(word_generator src/main.c)
target_link_libraries(word_generator PRIVATE word_generator_lib)

option(BUILD_TESTING "Build the GoogleTest test suite" ON)
if(BUILD_TESTING)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(word_generator_tests tests/test_word_generator.cpp)
    target_link_libraries(word_generator_tests
        PRIVATE word_generator_lib GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(word_generator_tests)
endif()
