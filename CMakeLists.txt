cmake_minimum_required(VERSION 3.10)

project(patent_system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    patent.hpp
    firm.hpp
    firmSys.hpp
    linked_list_template.hpp
    vector_template.hpp
)

add_executable(patent_system ${SOURCES})

target_include_directories(patent_system PUBLIC ${CMAKE_SOURCE_DIR}/data)