cmake_minimum_required(VERSION 3.6)
project(cpp_query_builder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Builder.cpp src/Builder.h src/Connection.cpp src/Connection.h src/Collection.cpp src/Collection.h)
add_executable(cpp_query_builder ${SOURCE_FILES})