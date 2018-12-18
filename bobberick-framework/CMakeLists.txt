set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")
enable_testing()
add_subdirectory(tests)
add_subdirectory(externals/tmxlite)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

set(
	SOURCE_FILES 
	src/entity/ECS.h 
	src/entity/Entity.h src/entity/Entity.cpp
	src/entity/EntityManager.cpp src/entity/EntityManager.h
	src/StateMachine.cpp src/StateMachine.h
	src/GameState.cpp src/GameState.h
	src/util/Vector2D.h src/util/Vector2D.cpp
	src/util/Timer.h src/util/Timer.cpp
	src/util/RandomGenerator.h src/util/RandomGenerator.cpp
	src/util/TextFormatter.h src/util/TextFormatter.cpp
	src/Game.cpp src/Game.h
	src/entity/components/SpriteComponent.cpp src/entity/components/SpriteComponent.h
	src/entity/components/RectangleComponent.cpp src/entity/components/RectangleComponent.h
	src/entity/components/TextComponent.cpp src/entity/components/TextComponent.h
	src/entity/components/TimerComponent.cpp src/entity/components/TimerComponent.h
	src/entity/components/FadeComponent.cpp src/entity/components/FadeComponent.h
	src/services/TextureManager.cpp src/services/TextureManager.h
	src/services/FontManager.cpp src/services/FontManager.h
	src/services/RectangleManager.cpp src/services/RectangleManager.h
	src/services/ServiceManager.cpp src/services/ServiceManager.h
	src/services/Service.cpp src/services/Service.h
	src/entity/Component.cpp src/entity/Component.h
	src/entity/components/TransformComponent.cpp src/entity/components/TransformComponent.h
	src/services/RenderService.cpp src/services/RenderService.h
	src/services/SettingsService.cpp src/services/SettingsService.h
	src/entity/systems/System.cpp src/entity/systems/System.h
	src/entity/systems/DrawSystem.cpp src/entity/systems/DrawSystem.h
	src/services/SoundManager.cpp src/services/SoundManager.h
	src/util/SDL_Deleter.h
    src/services/FrameHandler.cpp src/services/FrameHandler.h
	src/services/InputHandler.cpp src/services/InputHandler.h
	src/entity/systems/InputSystem.cpp src/entity/systems/InputSystem.h
	src/entity/components/ButtonSpriteComponent.cpp src/entity/components/ButtonSpriteComponent.h
	src/EmptyState.cpp src/EmptyState.h 
	src/LevelFactory.cpp src/LevelFactory.h 
	src/entity/components/TilesetComponent.cpp src/entity/components/TilesetComponent.h 
	src/entity/components/Tile.cpp src/entity/components/Tile.h 
	src/entity/components/TileObject.cpp src/entity/components/TileObject.h 
	src/entity/components/ButtonComponent.cpp src/entity/components/ButtonComponent.h
	src/entity/systems/GuiSystem.cpp src/entity/systems/GuiSystem.h
	src/entity/components/CollisionComponent.cpp src/entity/components/CollisionComponent.h
	src/entity/CollisionHelper.cpp src/entity/CollisionHelper.h
	src/services/SaveService.cpp src/services/SaveService.h
	externals/json/json.hpp
	src/entity/components/ParticleSystemComponent.cpp src/entity/components/ParticleSystemComponent.h src/entity/components/ParticleComponent.cpp src/entity/components/ParticleComponent.h src/entity/systems/ParticleSystem.cpp src/entity/systems/ParticleSystem.h)

add_library(bobberick-framework ${SOURCE_FILES})
target_link_libraries(bobberick-framework tmxlite)
target_link_libraries(bobberick-framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARY})
