cmake_minimum_required(VERSION 3.12)
project(bobberick-tools)

set(CMAKE_CXX_STANDARD 14)

set(BOBBERICK_VERSION 0.0.1)
set(CMAKE_C_COMPILER_INIT gcc)

message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG" )
    add_definitions(-D_DEBUG)
endif()

add_subdirectory(bobberick-framework)
add_subdirectory(bobberick-demo)