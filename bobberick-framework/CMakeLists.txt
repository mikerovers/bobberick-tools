set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")
enable_testing()
add_subdirectory(tests)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

#find_library(Box2D REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

set(
	SOURCE_FILES 
	
	 src/entity/Entity.cpp
	src/entity/EntityManager.cpp 
	src/StateMachine.cpp 
	src/GameState.cpp 
	src/util/Vector2D src/util/Vector2D.cpp
	src/Game.cpp 
	src/entity/components/SpriteComponent.cpp 
	src/entity/components/TextComponent.cpp 
	src/TextureManager.cpp 
	src/FontManager.cpp 
	src/services/ServiceManager.cpp 
	src/services/Service.cpp 
	src/entity/Component.cpp 
	src/entity/components/TransformComponent.cpp 
	src/services/RenderService.cpp 
	src/entity/systems/System.cpp 
	src/entity/systems/DrawSystem.cpp 
	src/SoundManager.cpp 
    src/util/FrameHandler.cpp 
	src/services/InputHandler.cpp 
	src/entity/systems/InputSystem.cpp 
	src/entity/components/CollisionComponent.cpp 
	src/entity/components/shapes/ChainShapeComponent.cpp 
	src/entity/components/shapes/CircleShapeComponent.cpp 
	src/entity/components/shapes/EdgeShapeComponent.cpp 
	src/entity/components/shapes/PolygonShapeComponent.cpp 
	src/entity/components/shapes/RectangleShapeComponent.cpp 
	src/entity/systems/CollisionSystem.cpp 
	src/services/WorldService.cpp 
)
add_library(bobberick-framework ${SOURCE_FILES})
if (MSVC)
	set_target_properties(bobberick-framework PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()
#add_library(Box2D ${SOURCE_FILES})
#include_directories(bobberick-framework Box2D)
include_directories(bobberick-framework src Box2D .)
target_link_libraries(bobberick-framework Box2D ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARY})
