set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/bobberick-framework/cmake/modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

set(SOURCE_FILES main.cpp 
BobberGame.cpp BobberGame.h 
systems/PlayerMovementSystem.cpp systems/PlayerMovementSystem.h 
components/PlayerMovementComponent.cpp components/PlayerMovementComponent.h
components/BulletMovementComponent.cpp components/BulletMovementComponent.h
components/PlayerComponent.cpp components/PlayerComponent.h 
components/SpawnComponent.cpp components/SpawnComponent.h 
components/ShootComponent.cpp components/ShootComponent.h 
components/SpawnedComponent.cpp components/SpawnedComponent.h 
components/StatsComponent.cpp components/StatsComponent.h
components/AIComponent.cpp components/AIComponent.h
components/HealthBarComponent.cpp components/HealthBarComponent.h
components/ItemComponent.h
components/AdvertisementComponent.cpp components/AdvertisementComponent.h
components/WeaponComponent.cpp components/WeaponComponent.h
components/InventoryComponent.cpp components/InventoryComponent.h
components/ButtonSettingComponent.cpp components/ButtonSettingComponent.h
systems/PlayerInputSystem.cpp systems/PlayerInputSystem.h
systems/CheatSystem.cpp systems/CheatSystem.h
systems/BulletSystem.cpp systems/BulletSystem.h
systems/ShieldSystem.cpp systems/ShieldSystem.h
systems/LevelSystem.cpp systems/LevelSystem.h
systems/HudSystem.cpp systems/HudSystem.h 
systems/MenuSystem.cpp systems/MenuSystem.h 
state/Level1State.cpp state/Level1State.h
systems/AISystem.cpp systems/AISystem.h 
systems/AdvertisementSystem.cpp systems/AdvertisementSystem.h 
state/StateFactory.cpp state/StateFactory.h
state/SplashScreenState.cpp state/SplashScreenState.h
state/SkillScreenState.cpp state/SkillScreenState.h
state/CreditScreenState.cpp state/CreditScreenState.h
state/SettingsScreenState.cpp state/SettingsScreenState.h
factory/ObjectFactory.cpp factory/ObjectFactory.h
factory/WeaponFactory.cpp factory/WeaponFactory.h
services/PlayerStatsService.cpp services/PlayerStatsService.h
factory/enemies/EnemyFactory.cpp factory/enemies/EnemyFactory.h
factory/enemies/BaseEnemyFactory.h
factory/enemies/OrcFactory.cpp factory/enemies/OrcFactory.h
factory/enemies/ChickenFactory.cpp factory/enemies/ChickenFactory.h
factory/enemies/ZombieFactory.cpp factory/enemies/ZombieFactory.h
factory/enemies/FireWizardFactory.cpp factory/enemies/FireWizardFactory.h
factory/enemies/EnemyManufactureFactory.cpp factory/enemies/EnemyManufactureFactory.h
state/TestState.cpp state/TestState.h
state/MainMenuState.cpp state/mainMenuState.h
factory/enemies/EndBossFactory.cpp factory/enemies/EndBossFactory.h 
factory/enemies/NullFactory.cpp factory/enemies/NullFactory.h 
state/HelpScreenState.cpp state/HelpScreenState.h 
state/EndScreenState.cpp state/EndScreenState.h 
state/Level2State.cpp state/Level2State.h
state/Level3State.cpp state/Level3State.h
state/PauseScreenState.cpp state/PauseScreenState.h)

add_executable(bobberick-demo ${SOURCE_FILES})

target_link_libraries(bobberick-demo bobberick-framework ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARY})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bobberick-demo)