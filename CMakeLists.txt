cmake_minimum_required(VERSION 3.25)
project(KathyGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(MY_FRAMEWORK_DIR "$ENV{HOME}/Documents/sdl_framework")

add_executable(MyGame
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/TextureManager.cpp
    src/TextureManager.h
    src/GameObject.cpp
    src/GameObject.h
    src/Map.cpp
    src/Map.h
    src/Vector2D.h
    src/Vector2D.cpp
    src/Collision.h
    src/Collision.cpp
    src/AssetManager.h
    src/AssetManager.cpp
    src/ECS/ECS.h
    src/ECS/ECS.cpp
    src/ECS/TransformComponent.h
    src/ECS/SpriteComponent.h
    src/ECS/KeyboardController.h
    src/ECS/ColliderComponent.h
    src/ECS/TileComponent.h
    src/ECS/ProjectileComponent.h
)

## Remove the need of relative path when including file 
target_include_directories(MyGame PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

## clean previous build
add_custom_target(CleanPreviousOutputs
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/asset"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/MyGame${CMAKE_EXECUTABLE_SUFFIX}"
    COMMENT "Wiping previous build assets and executable..."
)

## make sure the code use updated asset
add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/asset"
    "${CMAKE_CURRENT_BINARY_DIR}/asset"
)

add_dependencies(CopyAssets CleanPreviousOutputs)
add_dependencies(MyGame CopyAssets)

target_compile_options(MyGame PRIVATE "-F${MY_FRAMEWORK_DIR}")
target_link_options(MyGame PRIVATE "-F${MY_FRAMEWORK_DIR}")
target_link_options(MyGame PRIVATE "-Wl,-rpath,${MY_FRAMEWORK_DIR}")

target_link_libraries(MyGame PRIVATE
    "-framework SDL3"
    "-framework SDL3_image"
    "-framework SDL3_mixer"
    "-framework SDL3_ttf"
)
