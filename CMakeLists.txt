# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8.2)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "--Wall --Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Project's name
project(Downpour)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")
include_directories ("${CMAKE_SOURCE_DIR}/Dependencies/JobBot/source")
include_directories("${CMAKE_SOURCE_DIR}/Dependencies/googletest/googletest/include")

add_subdirectory(${CMAKE_SOURCE_DIR}/Dependencies/googletest EXCLUDE_FROM_ALL)

add_library(googletest STATIC IMPORTED)

add_executable(ResourceTestExe
  src/tests/ResourceTestMain.cpp
)

target_link_libraries(ResourceTestExe gtest_main)