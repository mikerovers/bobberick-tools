set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

set(SOURCE_FILES src/entity/ECS.h src/entity/Entity.h src/entity/Entity.cpp src/entity/EntityManager.cpp src/entity/EntityManager.h src/StateMachine.cpp src/StateMachine.h src/GameState.cpp src/GameState.h src/util/Vector2D.h src/util/Vector2D.cpp src/Game.cpp src/Game.h src/entity/components/SpriteComponent.cpp src/entity/components/SpriteComponent.h src/TextureManager.cpp src/TextureManager.h src/services/ServiceManager.cpp src/services/ServiceManager.h src/services/Service.cpp src/services/Service.h src/entity/Component.cpp src/entity/Component.h src/entity/components/TransformComponent.cpp src/entity/components/TransformComponent.h src/services/RenderService.cpp src/services/RenderService.h src/entity/systems/System.cpp src/entity/systems/System.h src/entity/systems/DrawSystem.cpp src/entity/systems/DrawSystem.h src/util/SDL_Deleter.h)
add_library(bobberick-framework ${SOURCE_FILES})

target_link_libraries(bobberick-framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})