cmake_minimum_required(VERSION 3.17)
project(blojzgame)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_DIR})



add_executable(blojzgame src/main.cpp src/Core/Engine.cpp src/Core/Engine.h src/Graphics/TextureManager.cpp src/Graphics/TextureManager.h src/Physics/Vector2D.h src/Physics/Transform.h src/Objects/GameObject.h src/Characters/Character.h src/Characters/Warrior.cpp src/Characters/Warrior.h src/Animations/SpriteAnimation.cpp src/Animations/SpriteAnimation.h src/Physics/RigidBody.h src/Inputs/Input.h src/Inputs/Input.cpp src/Timer/Timer.cpp src/Timer/Timer.h src/Maps/Layer.h src/Maps/GameMap.h src/Maps/TileLayer.cpp src/Maps/TileLayer.h src/Maps/MapParser.cpp src/Maps/MapParser.h src/Vendor/tinystr.cpp src/Vendor/tinystr.h src/Vendor/tinyxml.cpp src/Vendor/tinyxml.h src/Vendor/tinyxmlerror.cpp src/Vendor/tinyxmlparser.cpp src/Cameras/Camera.cpp src/Cameras/Camera.h src/Physics/Point.h src/Collision/CollisionHandler.cpp src/Collision/CollisionHandler.h src/Physics/Collider.h  src/Characters/Enemy.cpp src/Characters/Enemy.h src/Animations/Animation.h src/Characters/Animal.cpp src/Characters/Animal.h src/MainMenu/Menu.cpp src/MainMenu/Menu.h src/MainMenu/Text.h src/MainMenu/Text.cpp src/MainMenu/GameOver.cpp src/MainMenu/GameOver.h src/Characters/boss.cpp src/Characters/boss.h src/SaveAndLoad/saveAndLoad.cpp src/SaveAndLoad/saveAndLoad.h src/Replay/Replay.cpp src/Replay/Replay.h)

target_link_libraries(blojzgame ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})

