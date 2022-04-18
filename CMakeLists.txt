cmake_minimum_required(VERSION 3.14)
project(M4OEP-cchrist7-qwarden)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sfml.cpp)
add_executable(M4OEP-cchrist7-qwarden ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(M4OEP-cchrist7-qwarden sfml-system sfml-window sfml-graphics sfml-audio sfml-network)