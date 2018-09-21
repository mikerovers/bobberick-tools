set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(bobberick-demo ${SOURCE_FILES})

target_link_libraries(bobberick-demo bobberick-framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bobberick-demo)