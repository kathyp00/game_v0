cmake_minimum_required(VERSION 3.25)
project(LetsMakeGamesSDL3 CXX)

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
)

add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/asset"
    "${CMAKE_CURRENT_BINARY_DIR}/asset"
    COMMENT "Forcefully updating assets to match source folder..."
)

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
