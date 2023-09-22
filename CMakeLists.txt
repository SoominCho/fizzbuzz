cmake_minimum_required(VERSION 3.12) # version can be different

project(FizzBuzz_project) #name of your project

enable_testing() #to discover tests in test explorer 

add_library(fizzBuzz hiker.c)

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(mytests hikerTest.cpp) # add this executable

target_link_libraries(mytests PRIVATE fizzBuzz gtest) # link google test to this executable

include(GoogleTest)
gtest_discover_tests(mytests) # discovers tests by asking the compiled test executable to enumerate its tests