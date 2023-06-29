cmake_minimum_required(VERSION 3.25)

project(rand CXX)
set(CMAKE_CXX_STANDARD 20)

message("Downloading dependencies")
include(FetchContent)
FetchContent_Declare(
       googletest
       URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_library(rand_lib
        src/argument.cpp
        src/argument_parser.cpp
        src/utility.cpp)
target_include_directories(rand_lib PUBLIC "inc")

add_executable(rand src/main.cpp)

target_link_libraries(rand PRIVATE rand_lib)

add_executable(RandUnitTest
        test/argument_parser_test.cpp
        test/argument_test.cpp
        test/utility_test.cpp)

target_link_libraries(RandUnitTest PRIVATE rand_lib gmock gmock_main)