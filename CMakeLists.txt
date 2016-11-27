cmake_minimum_required(VERSION 3.6)
project(cpp_query_builder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libs/googletest)

include_directories(
        libs/googletest/googletest/include
        libs/googletest/googlemock/include
        src
)

set(SOURCE_FILES src/Builder.cpp src/Builder.h src/Connection.cpp src/Connection.h src/Collection.cpp src/Collection.h)
add_executable(cpp_query_builder ${SOURCE_FILES} main.cpp)

add_executable(builder_test ${SOURCE_FILES} test/builder_check.cpp test/test_shadow.h test/main.cpp)
target_link_libraries(builder_test gtest gtest_main)