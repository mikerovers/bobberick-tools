set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

set(SOURCE_FILES main.cpp BobberGame.cpp BobberGame.h
		state/StateFactory.cpp state/StateFactory.h
        state/SplashScreenState.cpp state/SplashScreenState.h)
add_executable(bobberick-demo ${SOURCE_FILES})

target_link_libraries(bobberick-demo bobberick-framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARY})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bobberick-demo)