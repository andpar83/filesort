cmake_minimum_required(VERSION 2.8.11)

project(file_sort)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

option(MSVC_WARNINGS_AS_ERRORS "Treats all compiler warnings as errors" ON)

file(GLOB my_src "*.h" "*.cpp")

add_executable(file_sort ${my_src})