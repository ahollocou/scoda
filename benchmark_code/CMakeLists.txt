cmake_minimum_required (VERSION 2.8.2)
PROJECT(scoda CXX)
SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)
SET(CMAKE_CXX_FLAGS "-O3 -std=c++11")	
INCLUDE_DIRECTORIES(./include)
project (DYCOLOA CXX)
FILE(GLOB COMMON_SOURCE_FILES "source/*.cpp")
add_executable(scoda "source/scoda/main.cpp" ${COMMON_SOURCE_FILES})
