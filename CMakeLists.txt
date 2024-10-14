cmake_minimum_required(VERSION 3.10)

project(patent_system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    ./src/main.cpp
)

add_executable(patent_system ${SOURCES})

include_directories(include)

target_include_directories(patent_system PUBLIC 
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_SOURCE_DIR}/templates
    ${CMAKE_SOURCE_DIR}/include
)