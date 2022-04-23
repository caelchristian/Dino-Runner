cmake_minimum_required(VERSION 3.14)
project(dino)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules") 
find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED) 

file(GLOB SOURCE_FILES
        *.cpp
        *.hpp
        )

include_directories(${SFML_INCLUDE_DIR})
add_executable(dino ${SOURCE_FILES}) 


target_link_libraries(dino ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})